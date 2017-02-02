-module(assignment4).

%% DO NOT CHANGE THE EXPORT STATEMENT!
-export([task/1, dist_task/1, pmap/2, faulty_task/1]).
%% End of no-change area

%ANTONINO SAULEO
%ASSIGNMENT 4

%%
%% Process handling
%%
%% Do not change the following two functions!
task(N) when N < 0; N > 100 ->
  exit(parameter_out_of_range);
task(N) ->
  timer:sleep(N * 2),
  256 + 17 *((N rem 13) + 3).

faulty_task(N) when N < 0; N > 100 ->
  exit(parameter_out_of_range);
faulty_task(N) ->
  timer:sleep(N * 2),
  {_,_,X} = now(),
  case X rem 10 == 0 of
    false ->
      256 + 17 *((N rem 13) + 3);
    true  ->
      throw(unexpected_error)
  end.

%%The first task is to implement a function dist_task/1. The function should, given
%%this list of numbers, spawn a process for each computation and collect all the
%%computation results.

%The OrderL does List comprehenssion where each value creates a new process Spawn that checks the value of X and does
% the functions task(Value) and the self() so this happens at the same time for each element of X.

  dist_task(Data) ->
    Spawn = fun(Value, Pid) -> %spawn takes a value and a PID for each element in the list then it returns a process.
      spawn(fun() ->
        NewValue = task(Value) , %here we start a process where the function task is run for the value
        Pid ! {self(), NewValue} %after the value is finished we send it to the process PID (for each value)
            end)
            end,
    NewList = [Spawn(X, self())|| X <- Data], %Here is where everything "STARTS" by going through all of the values in the list
    [receive {Pid, NewValue} -> NewValue end || Pid <- NewList]. %here the list go through all of their Pids and
    %the New Value is added with the individual Pid and we return the new values.


%%Your task is to implement the more general pmap/2, where the first
%%argument is the function to apply and the second argument is the list of data. You
%%should take into account the possibility of a function crashing, i.e. your
%%implementation should work also for the provided faulty_task/1, and not hang.
pmap(Function, Data) ->
    Spawn = fun(Value, Pid) ->
      spawn(fun() -> NewValue=
        try Function(Value) of
          Result -> Result
        catch
          Error -> Error
        end,
        Pid ! {self(), NewValue}
            end)
            end,
    NewList = [Spawn(X, self())|| X <- Data],
    [receive {Pid, NewValue} -> NewValue end || Pid <- NewList].



%%
%% Problem 4

% Due to the fact the last line test reads 3 it means that the function that will run first is add(P, 3), after that
% we know that g reads five so it means it adds 2 + 3 = 5. So lastly by default we know that f reads 6 because it would
% add 5 + 1 = 6. F wouldn't read first because then test would read 4 and G would read 6.
% So the answer of f is 6. :)