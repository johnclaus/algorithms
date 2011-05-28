-module(quicksort).
-export([quicksort_lc/1]).

quicksort_lc([]) -> [];
quicksort_lc([Head|Tail]) ->
	quicksort_lc([X||X <- Tail, X < Head]) ++ [Head] ++ quicksort_lc([X||X <- Tail, X >= Head]).