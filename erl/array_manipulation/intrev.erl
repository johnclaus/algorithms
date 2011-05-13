%% -------------------------------------------------------------
%%
%% The intrev function is a simple call which takes an integer
%% as input and returns the reversed input.
%%
%%	eg. '123' -> '321'
%%
%% -------------------------------------------------------------

-module(intrev).
-export([intrev/1]).

intrev(Integer) when is_integer(Integer) ->
	list_to_integer(lists:reverse(integer_to_list(Integer))).