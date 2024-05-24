# Lexer for C++ code
# José Manuel García Zumaya
# A01784238

defmodule Tfile do
  @doc """
  Function to extract all the tokens found in a text cpp file.
  Will scan every line individually.
  Arguments:
  - in_filename : the name of the file to read
  - out_filename : the name of a new file where emails will be stores, one in each line
  Returns:
  - html file with the tokens found
  """
  def get_tokens(in_filename, out_filename) do

    # Prepare the file to write the results
    {:ok, out_fd} = File.open(out_filename, [:write])
    # Start with the filename
    in_filename
    # Open the file to read it line by line
    |> File.stream!()
    # Scan each line to find tokens
    |> Enum.map(&find_token(&1))
    # Remove empty lists
    |> List.flatten()
    # Write the tokens into the output file
    |> doHtml(out_fd)
    # Close the output file
    File.close(out_fd)
  end

  @doc """
  Function to find all the tokens in a single line of text in recursive way.
  Arguments:
  - line : the line of text to scan
  Returns:
  - a list of tuples with token and match token found in the line
  """
def find_token(line), do: find_token(line, [])
defp find_token("", res), do: Enum.reverse(res)
defp find_token(line, res) do
  patterns = [
    {:reserved_word, ~r/^break\b|^try\b|^catch\b|^char\b|^class\b|^const\b|^continue\b|^default\b|^delete\b|^auto\b|^else\b|^friend\b|^for\b|^float\b|^long\b|^new\b|^operator\b|^private\b|^protected\b|^public\b|^return\b|^short\b|^sizeof\b|^static\b|^this\b|^typedef\b|^enum\b|^throw\b|^mutable\b|^struct\b|^case\b|^register\b|^switch\b|^and\b|^or\b|^namespace\b|^static_cast\b|^goto\b|^not\b|^xor\b|^bool\b|^do\b|^double\b|^int\b|^unsigned\b|^void\b|^virtual\b|^union\b|^while\b|^cout\b|^endl\b|^using\b|^if\b/},
    {:preprocessing, ~r/^#\w+/},
    {:library,  ~r/^[<][\w\.]+[>]/},
    {:newline, ~r/^\n+/},
    {:space, ~r/^\s/},
    {:special_symbol, ~r/^;/},
    {:structure_or_class_name, ~r/^\w+(?=\s*\{)/},
    {:structure_or_class_instance_declaration, ~r/^\w+(?=\s+\w+)/},
    {:curly_braces, ~r/^{|^}/},
    {:parenthesis, ~r/^\(|^\)/},
    {:function_name, ~r/^\w+(?=\s*\()/},
    {:integer_number, ~r/^[-+]?\d+\b(?!\.)/},
    {:float_number, ~r/^[+-]?\d*\.\d+/},
    {:operator, ~r/^\+(?!\+)|^\-(?!\-)|^\=(?!\=)|^\:(?!\:)|^\:\:|^\<(?!\<)|^\>(?!\>)|^\&(?!\&)|^\<\<|^\>\>|^\.|^\+\+|^\-\-|^\=\=|^\&\&|^\,/},
    {:string, ~r/^".*"/},
    {:comment, ~r/^\/\/.*|\/\*[\s\S]*?\*\//},
    {:variable, ~r/^\w+/}
  ]
  {token_type, token, remaining_line} =
    patterns
      |> Enum.find_value({nil, nil, line}, fn {type, pattern} ->
      case Regex.run(pattern, line, capture: :first) do
        [match] ->
          remaining = String.slice(line, String.length(match)..String.length(line))
          {type, match, remaining}
        nil -> false
      end
    end)
  find_token(remaining_line, [{token_type, token} | res])
end

def doHtml(list, out_fd) do
  IO.puts(out_fd, """
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <link rel="stylesheet" href="styles.css">
      <title>Document</title>
  </head>
  <body>
  <pre><code>
  """)
  html_content =
    Enum.map(list, fn {class, word} ->
      word = to_string(word)
      escaped_word = String.replace(word, "<", "&lt;")
                      |> String.replace(">", "&gt;")
      cond do
        class == :space -> " "
        class == :newline -> "\n"
        class == :library -> "<span class=\"#{class}\">#{escaped_word}</span>"
        true ->  "<span class=\"#{class}\">#{escaped_word}</span>"
      end
    end)
    |> Enum.join("")
  IO.puts(out_fd, html_content)
  IO.puts(out_fd, """
  </code></pre>
  </body>
  </html>
  """)
end
end

# Code to read a single command line argument
[in_filename] = System.argv()

# Create the name of the output file
# Add the string "-.tokens.html" before the extension
out_filename = String.replace(in_filename, ~r/(\.\w+$)/, "-tokens.html")
# Call the function to find tokens
Tfile.get_tokens(in_filename, out_filename)

# Now the program can be called as:
# elixir 07_file_io.exs example.cpp.txt
