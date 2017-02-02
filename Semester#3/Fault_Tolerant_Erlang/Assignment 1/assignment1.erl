-module(assignment1).

-export([even_odd/1, range_overlap/2, rect_overlap/2,
  get_amp/1, f2c/1, c2f/1, convert/1,
  measure/3, any_2_equal/3]).

%% Part 2 This code is done by Rafael Antonino Sauleo.
%% THE TEST SUITE RESULTS ARE WRITTEN DOWN IN THE END OF THE CODE! :)
%% ----------------------- eqc:module(assignment1_eqc).

%% It takes a value and if the reminder of the division is 0 it means it's even otherwise is odd.
%% I did the third part with an error in case someone doesn't put the correct input.
even_odd(Y) when Y >= 0 andalso (Y rem 2 =:= 0 ) -> even;
even_odd(Y) when Y > 0 andalso (Y rem 2 =/= 0 ) -> odd;
even_odd(_Y) -> error.

%% if X3 is bigger than X2 is not overlaping because they don't touch.
range_overlap({X1, X2}, {X3, X4}) when (X3 >= X2) or (X1 >=X4) -> no_overlap;
range_overlap({X1, X2}, {X3, X4}) -> range_overlap_aux(max(X1, X3), min(X2, X4));
range_overlap(_Something, _Something) -> error.
range_overlap_aux(MAX, MIN) -> {overlap, {MAX, MIN}}.


rect_overlap(_, _) -> ok.

%%here I created an error just in case someone puts a wrong input.
get_amp({amplifier, no_preamp, FACTOR, NOISE}) when FACTOR >= 0 andalso NOISE >=0 -> FACTOR;
get_amp({amplifier, {preamp, NUM}, FACTOR, NOISE}) when FACTOR >= 0 andalso NOISE >=0 -> FACTOR + NUM;
get_amp({_amplifier, _no_preamp, _FACTOR, _NOISE})  -> error.

%% it takes a value and transforms it to celsius.
f2c(Fahrenheit) -> ((Fahrenheit - 32)*5)/9.

%% it takes a value and transforms it to fahrenheit.
c2f(Celsius) -> (Celsius * (9/5)) + 32.

%% this function uses the functions above to convert, depending if you write f or c in the input.
convert({f, Fahrenheit}) -> {c, f2c(Fahrenheit)};
convert({c, Celsius}) -> {f, c2f(Celsius)}.

% Part 3
% -----------------------

%% the modified function it was asked to be done.
measure(X, N, N) -> X + 1;
measure(X, N, M)-> X + N - M.

%% it's true if two or more values are the same.
%% I created an error just in case a wrong input is received.
any_2_equal(N, N, M) -> true;
any_2_equal(N, M, N) -> true;
any_2_equal(M, N, N) -> true;
any_2_equal(N, N, N) -> true;
any_2_equal(N, M, P) -> false;
any_2_equal(_, _, _) -> error.


%TEST SUITE RESULTS

%%8> eqc:module(assignment1_eqc).
%%prop_even_odd: ....................................................................................................
%%OK, passed 100 tests
%%prop_range_overlap: ....................................................................................................
%%OK, passed 100 tests

%% THIS IS THE OPTIONAL PART.
%%prop_rect_overlap: Failed! After 1 tests.
%%{0,0,0,0,0,0,0,0}
%%Wrong output: assignment1:rect_overlap/2 applied to
%%[{rect,{0,0},{1,1}},{rect,{0,0},{1,1}}]
%%Returned: ok. Expected: {overlap,{rect,{0,0},{1,1}}}
%% END OF OPTIONAL PART

%%prop_get_amp: ....................................................................................................
%%OK, passed 100 tests
%%prop_f2c: ....................................................................................................
%%OK, passed 100 tests
%%prop_c2f: ....................................................................................................
%%OK, passed 100 tests
%%prop_convert: ....................................................................................................
%%OK, passed 100 tests
%%prop_measure: ....................................................................................................
%%OK, passed 100 tests
%%prop_any_2_equal: ....................................................................................................
%%OK, passed 100 tests
%%[prop_rect_overlap]
%%9>