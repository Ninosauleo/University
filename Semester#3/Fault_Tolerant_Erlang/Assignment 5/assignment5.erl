-module(assignment5).

-export([pmap/2]).

%% ANTONINO SAULEO

% Problem 1


%%Reimplement pmap() from assignment 4, so that it crashes when at least one of
%%the function invocations it executes crashes, instead of returning some of the
%%results. Furthermore, the function should cancel all remaining computations once
%%one of them crashes before terminating with a crash. Please use Erlang links to
%%solve this problem. Please implement your solution in the assignment5.erl
%%skeleton file.

pmap(Function, Data) ->
  Spawn = fun(Value, Pid) ->
    spawn_link(fun() -> NewValue=
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

% Problem 2 - Downtime

%PART A
%%Each node has a probability of failure of 1% in a given month, and it will take about 6h to fix a failure (or replace
%%a node) the probability for each node to be working properly (independently)  each month is 99% (100% - 1% = 99% = 0.99)
%%The probability for all nodes to be working properly together each month is 0,90438 (0.99^10 ~= 0,90438) so we know that
%%the probability of failure of all 10 nodes every month is 0,09562 (%1-0,90438 = 0,09562)if each month takes 6 hours to
%% fix each node it will take 0,57372 (0,09562*6 = 0,57372) to fix all. If we calculate this for each month of the year is
%% 0,57372*12 =6,88464 which is equal to 6.88 hours/year
%% FORMULA: (1 - 0.99 ^ 10) * 6hours * 12 months =  6.88 hours/year
%%Answer: the approximate downtime a year the system would have is around 6.88 hours/year

%PART B
%% In order for the system to fail we require at least 2 nodes failing so the probability for the 2 node to fail is
%% 0.08648275251 (1-0.99^9) from here we know that it takes 6 hours in order to fix a node. From here we divide by 730
%% hours which is the total amount of hours in a month and times 12 because we consider the downtime in a year.
%%FORMULA: (1-0.99^9) * 6 hours / (730 * 12) = 0.00005923476
%%ANSWER: 0.00005923476 hours/year



