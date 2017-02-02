-module(assignment2).

-export([price/1, stretch_if_square/1, convert/1, rect_overlap/2,
  print_n_0/1, print2_n_0/1,
  print_sum_0_n/1, lg/1, count_one_bits/1,
  print_bits/1, print_bits_rev/1,
  expand_circles/2, print_circles/1, even_fruit/1,
  ferry_vehicles/2, ferry_vehicles2/2
  , f2c/1, c2f/1, range_overlap/2, even_odd/1, print_0_n/1]).


% RAFAEL ANTONINO SAULEO

% 2. Refactoring

%The modified function instead of using if or case expression it uses guards.
price({A, N}) when A =:= 'apple' -> 11 * N;
price({A, N}) when A =:= 'orange' -> 15 * N + 2;
price({A, B, N}) when A =:= 'banana' andalso B =:= 'costarica' -> 8 * N;
price({A, B, N}) when A =:= 'banana' andalso B =:= 'equador' -> 9 * N + 2.


% Do not modify this function
rect_to_square({rect, A, A}) -> {square, A};
rect_to_square({rect, _, _}) -> not_square.

%It uses case expression so if the input is square turns it into a rectangle.
stretch_if_square(R) ->
  X = rect_to_square(R),
  case X of
    not_square -> R;
    {square, S} -> {rect, S, S*2}
  end.

%% it takes a value and transforms it to celsius.
f2c(Fahrenheit) -> ((Fahrenheit - 32)*5)/9.

%% it takes a value and transforms it to fahrenheit.
c2f(Celsius) -> (Celsius * (9/5)) + 32.

%Here I'm using case expression to use the functions of assignment 1.
convert(R) ->
  case R of
    {f, Farenheit} -> {c, f2c(Farenheit)};
    {c, Celsius} -> {f, c2f(Celsius)}
  end.

%COMMENT
%% if X3 is bigger than X2 is not overlaping because they don't touch.
range_overlap({X1, X2}, {X3, X4}) when (X3 >= X2) or (X1 >=X4) -> no_overlap;
range_overlap({X1, X2}, {X3, X4}) -> range_overlap_aux(max(X1, X3), min(X2, X4));
range_overlap(_Something, _Something) -> error.
range_overlap_aux(MAX, MIN) -> {overlap, {MAX, MIN}}.

%In this case when lines X overlaps and also Y, the rectangle overlaps.
rect_overlap({{X1, Y1}, {X2, Y2}}, {{X3, Y3}, {X4, Y4}}) ->
  case ({range_overlap({X1, X2}, {X3, X4}),range_overlap({Y1, Y2}, {Y3, Y4})}) of
    {{overlap, {MAX1, MIN1}}, {overlap, {MAX2, MIN2}}} -> {rect,{MAX1, MAX2}, {MIN1, MIN2}};
    _ -> no_overlap
  end.



% 3. Basic recursion

print_0_n(N, N) -> io:format("~p~n", [N]);
print_0_n(N, I) ->
  io:format("~p~n", [I]),
  print_0_n(N, I+1).

print_0_n(N) -> print_0_n(N, 0).

%create aux
print_n_0(N) -> print_aux(N, 0).

print_aux(N, N) -> io:format("~p~n", [N]);
print_aux(N, M) -> print_aux(N, M +1),
  io:format("~p~n", [M]).


% This function prints numbers from N to 0 separated by newlines and works recursively..
print2_n_0(0) -> io:format("~p~n", [0]);
print2_n_0(N) -> io:format("~p~n", [N]),
  print2_n_0(N - 1).


%This function when you type a number it generates an auxiliar function that starts a recursion where it
% prints numbers from 0 to N separated by newlines, and also computes the sum of numbers from 0 to N.

print_sum_0_n(N) -> print_sum_0_n_aux(N, 0, 0).

print_sum_0_n_aux(N, N, S) -> io:format("~p~n", [N]), N + S;
print_sum_0_n_aux(N, M, S) ->  io:format("~p~n", [M]), print_sum_0_n_aux(N, M+1, S+M).


% 4. Recursion on bits

lg(0) -> 0;
lg(N) -> 1 + lg(N div 2).

count_one_bits(0) -> 0;
count_one_bits(N) ->
  (N rem 2) + count_one_bits(N div 2).

% The function takes a number and prints its binary representation if the number starts with 0 it will skip that one
%that's why if you print 9 it prints more digits.
print_bits(0) -> ok;
print_bits(N) ->
  print_bits(N div 2), io:format("~p~n", [N rem 2]).

%same logic as above but it prints the reverse order.
print_bits_rev(0) -> ok;
print_bits_rev(N) ->
  io:format("~p~n", [N rem 2]), print_bits_rev(N div 2).

%It takes as arguments a positive integer N and a list of atom circle. I used pattern matching to expand the
%circle.
expand_circles(N, X) -> [{circle, A *N} || {circle, A} <- X].

%This function uses pattern matching in order to print a line ”Circle N” for each circle in the list.
print_circles(X) -> [io:format("~s ~p~n", ["Circle", A]) || {circle, A} <- X], ok.

%The function uses even_odd and pattern matching in order to print fruits with pair numbers.
even_odd(Y) when Y >= 0 andalso (Y rem 2 =:= 0 ) -> even;
even_odd(Y) when Y > 0 andalso (Y rem 2 =/= 0 ) -> odd;
even_odd(_Y) -> error.

even_fruit(X) -> [FRUIT || {FRUIT, A} <- X, even_odd(A) =:= even].

%The function uses patter matching in order to avoid car duplicates and also to avoid that the combined weight
%is not more that N.

ferry_vehicles(N, X) -> [{Vehicle1, Vehicle2, A + B} || {Vehicle1, A} <- X, {Vehicle2, B} <- X, Vehicle1 =/= Vehicle2,
  (A + B) =< N].

%The function uses patter matching in order to avoid car duplicates and also to avoid that the combined weight
%is not more that N but also avoids duplicate pairs.
ferry_vehicles2(N, X) -> [{Vehicle1, Vehicle2, A + B} || {Vehicle1, A} <- X, {Vehicle2, B} <- X,
  (A + B) =< N, Vehicle1 < Vehicle2].

%% TEST SUIT RESULTS! I tried the rectangle overlap but I still have some errors.
%%eqc:module(assignment2_eqc).
%%prop_price: ....................................................................................................
%%OK, passed 100 tests
%%prop_stretch_if_square: ....................................................................................................
%%OK, passed 100 tests
%%prop_convert: ....................................................................................................
%%OK, passed 100 tests
%%prop_rect_overlap: Failed! Reason:
%%{'EXIT',
%%{function_clause,
%%[{assignment2,rect_overlap,
%%[{rect,{0,0},{1,1}},{rect,{0,0},{1,1}}],
%%[{file,"assignment2.erl"},{line,55}]},
%%{assignment2_eqc,'-prop_rect_overlap/0-fun-3-',1,
%%[{file,"assignment2_eqc.erl"},{line,216}]}]}}
%%After 1 tests.
%%{0,0,0,0,0,0,0,0}
%%prop_print_0_n: ....................................................................................................
%%OK, passed 100 tests
%%prop_print_n_0: ....................................................................................................
%%OK, passed 100 tests
%%prop_print2_n_0: ....................................................................................................
%%OK, passed 100 tests
%%prop_print_sum_0_n: ....................................................................................................
%%OK, passed 100 tests
%%prop_lg: ....................................................................................................
%%OK, passed 100 tests
%%prop_count_one_bits: ....................................................................................................
%%OK, passed 100 tests
%%prop_print_bits: ....................................................................................................
%%OK, passed 100 tests
%%prop_print_bits_rev: ....................................................................................................
%%OK, passed 100 tests
%%prop_expand_circles: ....................................................................................................
%%OK, passed 100 tests
%%prop_print_circles: ....................................................................................................
%%OK, passed 100 tests
%%prop_even_fruit: ....................................................................................................
%%OK, passed 100 tests
%%prop_vehicles: ....................................................................................................
%%OK, passed 100 tests
%%prop_vehicles2: ....................................................................................................
%%OK, passed 100 tests
%%[prop_rect_overlap]

