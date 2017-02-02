-module(assignment3).

-export([sum/1, sum_interval/2, interval/2,
  sum_interval2/2, adj_duplicates/1,
  even_print/1, even_odd/1, even_print2/1,
  normalize/1, normalize2/1,
  sum2/1, last/1, mul/1, find/2, sort/1,
  dict_new/0, dict_get/2, dict_put/3,
  dict_wellformed/1, dict_map_values/2,
  tree_leaf/0, tree_branch/3, tree_deconstruct/1,
  tree_wellformed/1, tree_make_bfs/1, tree_bind/2,
  tree_flatten/1, tree_dfs/1, tree_sorted/1, tree_find/2,
  digitize/1, is_happy/1, all_happy/2,
  expr_eval/1, expr_print/1
  , max_num_aux/2]).


% 1. Basic functions, lists and tuples

% Do not modify this function
sum([])     -> 0;
sum([X|Xs]) -> X + sum(Xs).

sum_interval(N, M) when N > M -> 0;
sum_interval(N, M) -> N + sum_interval(N+1, M).

interval(N, M) when N > M -> [];
interval(N, M) -> [N |interval(N+1, M)].

sum_interval2(N, M) -> sum(interval(N, M)).

adj_duplicates([]) -> [];
adj_duplicates([L,L|Ls]) -> [ L | adj_duplicates([L|Ls]) ];
adj_duplicates([_|Ls])  -> adj_duplicates(Ls).

even_print([]) -> [];
even_print([L|Ls]) when (L rem 2 =:= 0)  -> [ io:format("The number is ~p~n", [L]) | even_print(Ls)];
even_print([L|Ls]) when (L rem 2 =:= 1)  -> even_print(Ls), ok.

even_odd(Y) when Y rem 2 =:= 0 -> even;
even_odd(Y) when Y rem 2 =/= 0 -> odd;
even_odd(_Y) -> error.

%even_print2([]) -> [];
even_print2(L) -> [ A || A <- L, even_odd(A) =:= even], ok.

normalize(X)-> [ A / max_num_aux(1, X) || A <- X ].

max_num_aux(X, []) when X >= 0 -> X;
max_num_aux(X, [H|T]) when X < H -> max_num_aux(H, T);
max_num_aux(X, [_|T]) -> max_num_aux(X, T).


normalize2(L) -> lists:map(fun(X) -> X / max_num_aux(1, L) end, L).

sum2(L)->
  case L of
    []-> 0;
    L -> hd(L) + sum2 (tl(L))
  end.


last([X]) -> X;
last([]) -> crash;
last([_|Ls]) -> Ls, last(Ls).

mul([]) ->1;
mul([X|Xs]) -> X * mul(Xs).


% VERSION 1 This will return the first value in the list that is true
find(_Fun, V) -> find_return([ VALUE ||  VALUE <- V, is_function(_Fun) =:= true andalso _Fun(VALUE) =:= true]).

find_return(L) ->
  case L of
    [] -> not_found;
    L -> {found, find_recursive(L)}
  end.

find_recursive([]) -> [];
find_recursive([X]) -> X;
find_recursive([L|Ls]) -> find_recursive(Ls), L.

%VERSION 2 This will return all the values that are true in a list.

%%WORKS BUT RETURNS A LIST WITH THE FOUND ELEMENTS
%%find(_Fun, V) -> find_return([ VALUE ||  VALUE <- V, is_function(_Fun) =:= true andalso _Fun(VALUE) =:= true]).
%%
%%find_return(L) ->
%%  case L of
%%    [] -> not_found;
%%    L ->  {found, L}
%%  end.


sort([]) -> [];
sort([Index|Ls])->
  sort([X || X <- Ls, X < Index]) ++ [Index] ++ sort([X || X <- Ls, X >= Index]).


% 3. Dictionary

dict_new() -> not_implemented.

dict_get(_, _) -> not_implemented.

dict_put(_, _, _) -> not_implemented.

dict_wellformed(_) -> not_implemented.

dict_map_values(_, _) -> not_implemented.


% 4. Trees

tree_leaf() -> not_implemented.

tree_branch(_, _, _) -> not_implemented.

tree_deconstruct(_) -> not_implemented.

tree_wellformed(_) -> not_implemented.

tree_make_bfs(_) -> not_implemented.

tree_bind(_, _) -> not_implemented.

tree_flatten(_) -> not_implemented.

tree_dfs(_) -> not_implemented.

tree_sorted(_) -> not_implemented.

tree_find(_, _) -> not_implemented.


% 5. Digitify a number 

digitize(N) when N<10, N >0 -> [N];
digitize(N) when N rem 10==0,N>9->digitize(N div 10)++[0];
digitize(N) when N >= 9-> digitize(N div 10) ++ digitize(N rem 10).


% 6. Happy numbers

is_happy(_N) -> not_implemented.

all_happy(_N, _M) -> not_implemented.


% 7. Expressions

expr_eval(_Expr) -> not_implemented.

expr_print(_Expr) -> not_implemented.



%TEST SUITE
%%
%%2> c(assignment3).
%%{ok,assignment3}
%%3> eqc:module(assignment3_eqc).
%%prop_sum: ....................................................................................................
%%OK, passed 100 tests
%%prop_sum_interval: ....................................................................................................
%%OK, passed 100 tests
%%prop_sum_interval2: ....................................................................................................
%%OK, passed 100 tests
%%prop_interval: ....................................................................................................
%%OK, passed 100 tests
%%prop_adj_duplicates: ....................................................................................................
%%OK, passed 100 tests
%%prop_even_print: Failed! After 1 tests.
%%[[]]
%%Wrong function result for [[]], expected ok, got []
%%prop_even_odd: ....................................................................................................
%%OK, passed 100 tests
%%prop_even_print2: .......Failed! After 8 tests.
%%[[0]]
%%Wrong printed output for [[0]], expected "0\n", got []
%%Shrinking x(0 times)
%%[[0]]
%%Wrong printed output for [[0]], expected "0\n", got []
%%prop_normalize: ......Failed! After 7 tests.
%%[-4]
%%{0,0.3333333333333333}
%%Given list [0.3333333333333333,-4], result was [0.3333333333333333,-4.0], but expected result was [1.0,
%%-12.0]
%%Shrinking .x.(2 times)
%%[]
%%{0,0.5}
%%Given list [0.5], result was [0.5], but expected result was [1.0]
%%prop_normalize2: .................Failed! After 18 tests.
%%[]
%%{0,0.3333333333333333}
%%Given list [0.3333333333333333], result was [0.3333333333333333], but expected result was [1.0]
%%Shrinking .x.(2 times)
%%[]
%%{0,0.5}
%%Given list [0.5], result was [0.5], but expected result was [1.0]
%%prop_sum2: ....................................................................................................
%%OK, passed 100 tests
%%prop_last: Failed! After 1 tests.
%%[]
%%Result: crash, expected a crash
%%prop_mul: ....................................................................................................
%%OK, passed 100 tests
%%prop_find: ....................................................................................................
%%OK, passed 100 tests
%%prop_sort: ....................................................................................................
%%OK, passed 100 tests
%%prop_dict_new: Failed! After 1 tests.
%%Wrong output: assignment3:dict_new/0 applied to
%%[]
%%Returned: not_implemented. Expected: {dict,[]}
%%prop_dict_get: Failed! After 1 tests.
%%{{dict,[]},pineapple}
%%Wrong output: assignment3:dict_get/2 applied to
%%[{dict,[]},pineapple]
%%Returned: not_implemented. Expected: not_found
%%Shrinking .(1 times)
%%{{dict,[]},apple}
%%Wrong output: assignment3:dict_get/2 applied to
%%[{dict,[]},apple]
%%Returned: not_implemented. Expected: not_found
%%prop_dict_put: Failed! After 1 tests.
%%{{dict,[]},pear,4}
%%Wrong output: assignment3:dict_put/3 applied to
%%[{dict,[]},pear,4]
%%Returned: not_implemented. Expected: {{dict,[{pear,4}]},fresh} (or similar)
%%Shrinking ..(2 times)
%%{{dict,[]},apple,0}
%%Wrong output: assignment3:dict_put/3 applied to
%%[{dict,[]},apple,0]
%%Returned: not_implemented. Expected: {{dict,[{apple,0}]},fresh} (or similar)
%%prop_dict_wellformed: Failed! After 1 tests.
%%{dict,[]}
%%Wrong output: assignment3:dict_wellformed/1 applied to
%%[{dict,[]}]
%%Returned: not_implemented. Expected: true
%%prop_dict_map_values: Failed! After 1 tests.
%%[]
%%{{dict,[]},{'-',0}}
%%Wrong output: assignment3:dict_map_values/2 applied to
%%[fun (X) -> X - 0 end, {dict,[]}]
%%Returned: not_implemented. Expected: {dict,[]} (or similar)
%%Shrinking .(1 times)
%%[]
%%{{dict,[]},{'<',0}}
%%Wrong output: assignment3:dict_map_values/2 applied to
%%[fun (X) -> X < 0 end, {dict,[]}]
%%Returned: not_implemented. Expected: {dict,[]} (or similar)
%%prop_tree_basic: Failed! After 1 tests.
%%tree_leaf
%%Test case
%%[tree_leaf]
%%Returned: {wrong_result,not_implemented}. Expected: dec_leaf
%%prop_tree_wellformed: Failed! After 1 tests.
%%tree_leaf
%%Test case
%%[tree_leaf]
%%Returned: not_implemented. Expected: true
%%prop_tree_make_bfs: Failed! After 1 tests.
%%[]
%%Test case
%%[[]]
%%Returned: {wrong_result,not_implemented}. Expected: dec_leaf
%%prop_tree_bind: Failed! After 1 tests.
%%{tree_leaf,tree_leaf}
%%Test case
%%[{tree_leaf,tree_leaf}]
%%Returned: {wrong_result,not_implemented}. Expected: dec_leaf
%%prop_tree_flatten: Failed! After 1 tests.
%%tree_leaf
%%Test case
%%[tree_leaf]
%%Returned: {wrong_result,not_implemented}. Expected: {wrong_result,[]}
%%prop_tree_dfs: Failed! After 1 tests.
%%tree_leaf
%%Test case
%%[tree_leaf]
%%Returned: not_implemented. Expected: []
%%prop_tree_sorted: Failed! After 1 tests.
%%tree_leaf
%%Test case
%%[tree_leaf]
%%Returned: not_implemented. Expected: true
%%prop_tree_find: Failed! After 1 tests.
%%{tree_leaf,tree_leaf}
%%Test case
%%[tree_leaf,tree_leaf]
%%Returned: not_implemented. Expected: true
%%prop_digitize: ....................................................................................................
%%OK, passed 100 tests
%%prop_is_happy: Failed! After 1 tests.
%%1533
%%Wrong output: assignment3:is_happy/1 applied to
%%[1533]
%%Returned: not_implemented. Expected: true
%%Shrinking .(1 times)
%%1
%%Wrong output: assignment3:is_happy/1 applied to
%%[1]
%%Returned: not_implemented. Expected: true
%%prop_all_happy: Failed! After 1 tests.
%%{1031,1761}
%%Wrong output: assignment3:all_happy/2 applied to
%%[1031,1761]
%%Returned: not_implemented. Expected: [1033,1039,1067,1076,1088,1090,1092,1093,
%%1112,1114,1115,1121,1122,1125,1128,1141,
%%1148,1151,1152,1158,1177,1182,1184,1185,
%%1188,1209,1211,1212,1215,1218,1221,1222,
%%1233,1247,1251,1257,1258,1274,1275,1277,
%%1281,1285,1288,1290,1299,1300,1303,1309,
%%1323,1330,1332,1333,1335,1337,1339,1353,
%%1366,1373,1390,1393,1411,1418,1427,1444,
%%1447,1448,1457,1472,1474,1475,1478,1481,
%%1484,1487,1511,1512,1518,1521,1527,1528,
%%1533,1547,1557,1572,1574,1575,1578,1581,
%%1582,1587,1599,1607,1636,1663,1666,1670,
%%1679,1697,1706,1717,1724,1725,1727,1733,
%%1742,1744,1745,1748,1752,1754,1755,1758,
%%1760]
%%Shrinking ..(2 times)
%%{1,1}
%%Wrong output: assignment3:all_happy/2 applied to
%%[1,1]
%%Returned: not_implemented. Expected: [1]
%%prop_expr_eval: Failed! After 1 tests.
%%{num,0}
%%Wrong output: assignment3:expr_eval/1 applied to
%%[{num,0}]
%%Returned: not_implemented. Expected: 0
%%prop_expr_print: Failed! After 1 tests.
%%{num,0}
%%Wrong output: assignment3:expr_print/1 applied to
%%[{num,0}]
%%Returned: not_implemented. Expected: "0"
%%[prop_even_print,prop_even_print2,prop_normalize,
%%prop_normalize2,prop_last,prop_dict_new,prop_dict_get,
%%prop_dict_put,prop_dict_wellformed,prop_dict_map_values,
%%prop_tree_basic,prop_tree_wellformed,prop_tree_make_bfs,
%%prop_tree_bind,prop_tree_flatten,prop_tree_dfs,
%%prop_tree_sorted,prop_tree_find,prop_is_happy,
%%prop_all_happy,prop_expr_eval,prop_expr_print]
%%4>
%%
