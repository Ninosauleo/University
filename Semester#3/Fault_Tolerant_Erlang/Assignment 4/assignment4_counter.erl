-module(assignment4_counter).

%% DO NOT CHANGE THE EXPORT STATEMENT!
-export([start/0, init/0, incr/1, fetch/1, reset/1, stop/1
]).


%Antonino Sauleo
%Assignment4

%%should spawn a new server process and return its PID. Independent calls to
%%start/0 should create different instances of the server. The server process should run
%%the init/0 function, which should initialise its state with the integer 0.

  start() -> spawn (fun() -> init() end).
  init() -> serverLoop(0). %here the process initialise with cero.

  serverLoop(N) ->
    receive
    %here the server receives the message from incr and sends {get, ok} and after that it adds one to the current value
      {increment, Pid} -> Pid ! {get, ok}, serverLoop(N +1);
    %here the server receives the message from fetch and sends the message {get,N} N is the current value inside the server
      {retreive, Pid} -> Pid ! {get, N}, serverLoop(N);
    %here the server receives the message from reset and it sends the message {get, ok} and replaces the value to 0
      {reset, Pid} -> Pid ! {get, ok}, serverLoop(0)
    end.

%%incr(S) should add 1 to the state of the server identified by the PID S. The function
%%should return the atom ok once the update had been performed.
  incr(Pid) -> Pid ! {increment, self()},
    receive
      {get, ok} -> ok
    end.

%%fetch(S) should read the state of the server identified by the PID S and return it.
  fetch(Pid) -> Pid ! {retreive, self()},
  receive
    {get, N} -> N
  end.

%%reset(S) should reset to 0 the state of the server identified by the PID S. The
%%function should return the atom ok once the update had been performed.
  reset(Pid) -> Pid ! {reset, self()},
  receive
    {get, ok} -> ok
  end.

%%stop(S) should terminate the server process
  stop(Pid) -> exit(Pid, kill), ok.
