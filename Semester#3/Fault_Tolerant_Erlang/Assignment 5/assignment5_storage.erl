-module(assignment5_storage).

%% DO NOT CHANGE THE EXPORT STATEMENT!
-export([start/0, init/0, stop/0, store/2, fetch/1, flush/0, client_monitor/1]).
%% End of no-change area

start() ->
	Pid = whereis(sts),
	if
	%If whereis(sts) is undefined it means the process has not been started so we register it and after that we return
	% {ok, whereis(sts)} so we know the Pid.
		Pid == undefined -> register (sts, spawn(fun()-> init() end)), {ok, whereis(sts)};
	%If the process already started it will return {ok, Pid}
		true -> {ok,Pid}
	end.

init() ->  serverloop([]).

serverloop(L)->

	receive
	%here the server receives the a tuple from store/2 and we use proplists:getvalue to check if the value in with
	%that key already exists, if it does not exist we send a message {ok, no_value} otherwise we send {ok, Value1}
		{Pid, {store, Key, Value}} ->
			case proplists:get_value({Pid, Key}, L) of
				%here you spawn a supervisor for each new client
				undefined -> Pid ! {ok, no_value}, spawn(?MODULE, client_monitor, [Pid]);
				Value1 -> Pid ! {ok, Value1}
			end,
			%here we add an element containing {{Pid, key}, Value} to a List that is returned by proplists:delete which returns
			%a list that deletes all entries associated with Key from the List.
			serverloop([{{Pid, Key}, Value}] ++ proplists:delete({Pid,Key},L));

	%here the server receives a tuple from the fetch client and we use proplists:get_value if we get undefined it means
	%there is nothing in the list with that key otherwise we return the value.
		{Pid, {fetch, Key}} ->
			case proplists:get_value({Pid, Key}, L) of
				undefined -> Pid ! {error, not_found}, spawn(?MODULE, client_monitor, [Pid]);
				Value1 -> Pid ! {ok, Value1}
			end,
			%here we don't modify the values in the list
			serverloop(L);

	%here the server receives a tuple from the flush client and we return ok, a list comprehenssion where
	%we go through all of the list in the server and we return a new list.
		{Pid, flush} -> ok,
			List =[ {{OldPid, Key},Value} || {{OldPid, Key},Value} <- L, OldPid =/= Pid],
			Pid ! {ok,flushed},
			serverloop(List)

	end.

client_monitor(Pid) ->
	%monitor Pid (caller process) wait for the 'DOWN' msg then send a flush request with it's PID
	%call this process whenever we have a new client request
	spawn(fun()-> erlang:monitor(process,Pid), receive _ -> sts ! {Pid, flush} end end).


stop() ->
	case whereis(sts) of
		undefined -> already_stopped;
		_Else -> exit(whereis(sts), kill), stopped
	end.

%% store/2 stores a new on the server, while returning ok and the old value (or
%% no_value, if the key has not been used before!).
%% here store sends a message to the server (sts) a tuple that contains the {client Pid, {store, key, Value}}
store(Key, Value) -> sts ! {self(), {store, Key, Value}},
	receive
		Store_Message -> Store_Message

	end.

%fetch/1 returns either {ok, Value} or {error, not_found}. fetch/1 does not change the stored term.
fetch(Key) -> sts ! {self(), {fetch,Key}},
	receive
		Fetch_Message -> Fetch_Message
	end.

%flush/0 removes all terms for the calling process
flush() -> sts ! {self(),flush},
	receive
		{ok,flushed} -> {ok,flushed}
	end.