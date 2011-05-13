%% -------------------------------------------------------------
%%
%% The strrev_by_char function is a simple call which takes a string
%% as input and returns the reversed input by characters.
%%
%%	eg. 'abc' -> 'cba'
%%		'abcdef ghij' -> 'jihg fedcba'
%%
%% -------------------------------------------------------------

-module(strrev).
-export([strrev_by_char/1]).

strrev_by_char(String) when is_list(String) ->
	lists:reverse(String).