# Parsing a string in token types, use of automata deterministic
# An automata is definided by: {delta, accept, q0}
# where, delta is the transition function wich receives the current state and the current character
# and returns the next state and if the token is found
# accept is the list of accept states
# q0 is the initial state
# Use of pattern matching, tail recursion, and list management

# José Manuel García Zumaya A01784238
# 26 - 04 - 2024

defmodule Parsing.TokenList do

  def evaluate_3({first, middle, _last}, string) do #Function that recives a automata and string
    automata = {&Parsing.TokenList.delta_arithmetic/2, middle, first}
    string
    |> String.graphemes() # Split the string into characters
    |> eval_dfa(automata, [], []) # Call the function eval_dfa with the string, automata, an empty list to save the tokens and an empty list to save the characters in one token
  end
  def arithmetic_lexer(string) do #Function that receives a string with an automata defined already
    automata = {&Parsing.TokenList.delta_arithmetic/2, [:int, :float, :exp, :par_open, :par_close, :var, :nspace], :start}
    string
    |> String.graphemes()
    |> eval_dfa(automata, [], [])
  end

  def eval_dfa([], {_delta, accept, state}, tokens, characters) do #This functions is called when the characters of the string have finished
    clean_tuple = fn {key, value} -> #Function to clean one tuple of spaces
      {key, String.trim(value)}
    end
    cond do
      Enum.member?(accept, state) == true -> [{state, Enum.reverse(characters) |> Enum.join("")} | tokens] |> Enum.reverse() |> Enum.map(clean_tuple) |>
      Enum.reject(fn {key, _value} -> key == :nspace end) #This condition first evaluate if the actual state is an accept state, if it is,
      # it creates a tuple with the state and the characters of the token, then it reverse the list of characters to read correct then reverse the list of tokens,
      # clean the spaces of the elements in each tuple,
      # and the last function to exclude the last token if it is a space, meaning that string ends in space
      true -> false #If the state is not an accept state, return false
    end
  end

  def eval_dfa([char | tail], {delta, accept, state}, tokens, characters) do #This function is called when the characters of the string have not finished
     [new_state , found] = delta.(state, char) #Call the transition function with the current state and the current character and save the new state and if the token is found
     up_characters = [char | characters] # Add the current character to the list of characters
     #binding() |> IO.inspect()
    cond do
      found == false -> eval_dfa(tail, {delta, accept, new_state}, tokens, up_characters) #If the token is not found, call the function with the new state and
      # the tail of list of characters, don't change the list of tokens and keep the list of characters in the current state
      true ->
        new_token = {found, Enum.reverse(tl(up_characters)) |> Enum.join("")} #If the token is found, create a tuple with the token and the characters of the token
        eval_dfa(tail, {delta, accept, new_state}, [new_token | tokens], [hd(up_characters)]) #Call the function with the new state,
        # and add the new token to the list of tokens, and keep the first character of the list of characters to use in the next step of the recursion
    end
  end

  def delta_arithmetic(start, char) do #Transition function
  # The detailed explanation of the transitions it can be found in the graph of the automata
    case start do #Case to evaluate the current state
      :start -> cond do # If the current state is :start
        is_sign(char) -> [:sign, false]
        is_digit(char) -> [:int, false]
        char == "(" -> [:par_open, false]
        char == ")" -> [:par_close, false]
        char == " " -> [:space, false]
        is_alphaN(char) -> [:var, false]
        true -> [:fail, false]
      end

      :int -> cond do # If the current state is :int
        is_digit(char) -> [:int, false]
        is_operator(char) -> [:oper, :int]
        char == "." -> [:dot, false]
        char == "e" || char == "E" -> [:e, false]
        char == ")" -> [:par_close, :int]
        char == " " -> [:nspace, :int]
        true -> [:fail, false]
      end

      :dot -> cond do # If the current state is :dot
        is_digit(char) -> [:float, false]
        true -> [:fail, false]
      end

      :float -> cond do # If the current state is :float
        is_digit(char) -> [:float, false]
        is_operator(char) -> [:oper, :float]
        char == ")" -> [:par_close, :float]
        char == "e" || char == "E" -> [:e, false]
        char == " " -> [:nspace, :float]
        true -> [:fail, false]
      end

      :oper -> cond do # If the current state is :oper
        is_sign(char) -> [:sign, :oper]
        is_digit(char) -> [:int, :oper]
        is_alphaN(char) -> [:var, :oper]
        char == "(" -> [:par_open, :oper]
        char == " " -> [:space, :oper]
        true -> [:fail, false]
      end

      :sign -> cond do # If the current state is :sign
        is_digit(char) -> [:int, false]
        char == "(" -> [:par_open, false]
        true -> [:fail, false]
      end

      :e -> cond do # If the current state is :e
        is_digit(char) -> [:exp, false]
        is_sign(char) -> [:esign, false]
        true -> [:fail, false]
      end

      :esign -> cond do # If the current state is :esign
        is_digit(char) -> [:exp, false]
        true -> [:fail, false]
      end

      :exp -> cond do # If the current state is :exp
        is_digit(char) -> [:exp, false]
        is_operator(char) -> [:oper, :exp]
        char == ")" -> [:par_close, :exp]
        true -> [:fail, false]
      end

      :par_open -> cond do # If the current state is :par_open
        is_digit(char) -> [:int, :par_open]
        is_operator(char) -> [:oper, :par_open]
        is_alphaN(char) -> [:var, :par_open]
        char == "(" -> [:par_open, :par_open]
        char == ")" -> [:par_close, :par_close]
        char == " " -> [:space, :par_open]
        true -> [:fail, false]
      end

      :par_close -> cond do # If the current state is :par_close
        is_operator(char) -> [:oper, :par_close]
        char == "(" -> [:par_open, :par_open]
        char == ")" -> [:par_close, :par_close]
        char == " " -> [:nspace, :par_close]
        true -> [:fail, false]
      end
      # :parenthesis -> cond do
      #   is_digit(char) -> [:int, :parenthesis]
      #   is_operator(char) -> [:oper, :parenthesis]
      #   is_alphaN(char) -> [:var, :parenthesis]
      #   char == "(" || char == ")" -> [:parenthesis, :parenthesis]
      #   char == " " -> [:space, :parenthesis]
      #   true -> false
      # end
      :var -> cond do # If the current state is :var
        is_digit(char) -> [:var, false]
        is_operator(char) -> [:oper, :var]
        is_alphaN(char) -> [:var, false]
        char == ")" -> [:par_close, :var]
        char == " " -> [:nspace, :var]
        true -> [:fail, false]
      end

      :nspace -> cond do # If the current state is :nspace
        char == " " -> [:nspace, false]
        char == ")" -> [:par_close, false]
        is_operator(char) -> [:oper, false]
        true -> [:fail, false]
      end

      :space -> cond do # If the current state is :space
        char == " " -> [:space, false]
        is_digit(char) -> [:int, false]
        is_alphaN(char) -> [:var, false]
        is_operator(char) -> [:oper, false]
        char == "(" -> [:par_open, false]
        true -> [:start, false]
      end

      :fail -> [:fail, false] # If the current state is :fail

    end
  end

  # Functions to check if a character is a digit, a sign, an operator or an alphanumeric character, keeping the rules
  def is_digit(char) do
    "0123456789"
    |> String.graphemes()
    |> Enum.member?(char)
  end

  def is_sign(char) do
    Enum.member?(["+", "-"], char)
  end

  def is_operator(char) do
    Enum.member?(["+", "-", "*", "/", "%", "^", "="], char)
  end

  def is_alphaN(char) do
    lowercase = ?a..?z |> Enum.map(&<<&1::utf8>>) # Create a list with the lowercase characters
    uppercase = ?A..?Z |> Enum.map(&<<&1::utf8>>) # Create a list with the uppercase characters
    Enum.member?(lowercase ++ uppercase ++ ["_"], char)
  end
end
