# The automata argument is expressed as:
  # {delta, accept, q0}
  def arithmetic_lexer(string) do
    automata = {&DFA.delta_arithmetic/3, [:int, :float], :start}
    string
    |> String.graphemes() # Split the string into characters
    |> eval_dfa(automata, [], [])
  end

  def eval_dfa([], {_delta, accept, state}, tokens, info) do
    cond do
      Enum.member?(accept, state) == true -> [{state, Enum.reverse(info) |> Enum.join("")} | tokens] |> Enum.reverse()
      true -> false
    end

    # Enum.member?(accept, state) # Check if the final state is in the accept states, si a lista de estados de aceptacion contiene a state
  end
  def eval_dfa([char | tail], {delta, accept, state}, tokens, info) do
    #binding() |> IO.inspect()
    [new_state, found, data] = delta.(state, char, info) # de la funcion delta, se le pasa el estado actual y el caracter actual, delta es el parametro y el "nuevo nombre" con el cual podemos acceder
    cond do
      found == false -> eval_dfa(tail, {delta, accept, new_state}, tokens, data)
      true -> eval_dfa(tail, {delta, accept, new_state}, [{found, Enum.reverse(tl(data)) |> Enum.join("")} | tokens], [hd(data)])
    end
    #dentro de la funcion eval_dfa
    # eval_dfa(tail, {delta, accept, new_state}, res)
  end
