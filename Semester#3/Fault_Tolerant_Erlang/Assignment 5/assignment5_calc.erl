-module(assignment5_calc).

-export([start_link/1, add/2, mul/2, stop/0, fake_random/1, client/3, jobs/1]).

%% ANTONINO SAULEO

start_link(M) ->
  S = spawn_link(fun () -> loop(M) end),
  register(calc, S),
  {ok, S}.

fake_random(N) ->
  M = erlang:monotonic_time(),
  (M rem 2147483647) rem N == 0.

% Choose between good and bad execution at random.
% If the first argument is ok, then only good execution is chosen.
% Otherwise, good is chosen with likelyhood (N-1)/N;
% bad is chosen with likelyhood 1/N.
fault(ok, Good, _  ) -> Good();
fault(N , Good, Bad) ->
  case fake_random(N) of
    true  -> Bad();
    false -> Good()
  end.

% Server loop, which may exhibit erroneous
% behaviour depending on the argument.
% If the argument is:
% * no_fault, there are no errors
% * transient_fault, there may be transient errors.
loop(M) ->
  % If M is transient_fault then a transient fault
  % has a 1/10 chance of occurring.
  R = case M of
        transient_faults -> 10;
        no_faults        -> ok
      end,
  receive
    {add, P, A, B} ->
      fault(R, fun () -> P ! {add_reply, A + B} end,
        fun () -> io:format("Transient fault occurred~n") end),
      loop(M);
    {mul, P, A, B} ->
      fault(R, fun () -> P ! {mul_reply, A * B} end,
        fun () -> io:format("Transient fault occurred~n") end),
      loop(M);
    stop -> ok
  end.

% Add two numbers
% Timeout after 3 seconds
add(A, B) ->
  calc ! {add, self(), A, B},
  receive
    {add_reply, C} -> C
  after 1000 -> error(no_response)
  end.

% Multiply two numbers
% Timeout after 3 seconds
mul(A, B) ->
  calc ! {mul, self(), A, B},
  receive
    {mul_reply, C} -> C
  after 1000 -> error(no_response)
  end.

stop() ->
  calc ! stop.

sup_start_link(M) ->
  spawn_link(fun () -> sup(M) end).

sup(M) ->
  process_flag(trap_exit, true),
  {ok, _Pid} = start_link(M),
  receive
    {'EXIT', _From, normal} ->
      ok; % Normal termination; don't restart the server
    {'EXIT', _From, _Reason} ->
      sup(M) % Crash: restart
  end.

client(X, Y, Z) ->
  Q = mul(X, Y),
  R = add(Q, 3),
  mul(R, Z).

report(X) ->
  io:format("Job returned ~p~n", [X]).

jobs(M) ->
  sup_start_link(M),
  timer:sleep(10), % We wait a bit for the calc process to be registered.
  % This is a bad solution: normally this is handled by the OTP framework.
  L = [fun () -> catch client(1, 2, 3) end,
    fun () -> catch client(2, 3, 7) end,
    fun () -> catch client(5, 4, 2) end,
    fun () -> catch client(4, 10, 7) end,
    fun () -> catch client(3, 5, 2) end],
  [report(check_loop(F,0)) || F <- L], %%it will run a loop trying to reach the client
  stop().


%if it has been pinged the 3rd time,then exit with error
check_loop(_F,3) -> error(client_does_not_respond); %%this will count until it says says trying again 3
check_loop(F,Counter) -> case F() of
                           {'EXIT',_} -> io:format("Trying again ~p", [Counter+1]),check_loop(F,Counter+1);
                           Variable -> Variable
                         end.


%Question
%When you run assignment5_calc:jobs(transient_faults), it might hang.
%Explain what is the problem. Does the server process crash?

%ANSWER:
%when the transient_faults happens it runs the functions add() and mul() but it hangs (not crashes) because it's expecting
% an answer as the functions are not sending a message back.


