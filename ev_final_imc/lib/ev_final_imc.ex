# Reading and writing into files with Elixir
# Also using regular expressions
#
# Gilberto Echeverria
# 2024-04-30

defmodule Tfile do

  @doc """
  Function to extract all the emails found in a text file.
  Will scan every line individually.
  Arguments:
  - in_filename : the name of the file to read
  - out_filename : the name of a new file where emails will be stores, one in each line
  Returns:
  - :ok
  - As a side effect, a new file is created
  """
  @spec get_emails(String.t(), String.t()) :: :ok
  def get_emails(in_filename, out_filename) do

    # Prepare the file to write the results
    {:ok, out_fd} = File.open(out_filename, [:write])

    # Start with the filename
    in_filename
    # Open the file to read it line by line
    |> File.stream!()
    # Scan each line to find email addresses
    #|> Enum.map(&Regex.scan(~r/\w+@\w+\.\w{2,4}/, &1))
    # Another syntax for the anonymous function to the map
    #|> Enum.map(fn line -> Regex.scan(~r/\w+@\w+\.\w{2,4}/, line) end)
    # Using a named function instead
    |> Enum.map(&find_token(&1))
    |> IO.inspect(label: "After scan")
    # Eliminate lines without an email
    |> Enum.filter(&(&1 != []))
    |> IO.inspect(label: "After filter")
    # Remove the lists containing the emails
    |> List.flatten()
    #|> Enum.map(&hd/1)
    #|> Enum.map(&hd/1)
    |> IO.inspect(label: "After getting the heads of the lists")
    # Write each line to the file
    |> doHtml(out_fd)
    File.close(out_fd)
  end

  # Enum.map(fn {tag, word} ->
  #   IO.puts(out_fd, "#{tag}: #{word}")
  # end)

  @doc """
  Function to look for an email address inside a string
  Arguments:
  - line : a string
  Returns:
  - A list, either empty if no matches were found, or containing lists of matches
  """
  # @spec find_token(String.t()) :: List
  # def find_token(line), do: find_token(line, [])
  # defp find_token("", res), do: res
  # defp find_token(line, res) do
  #   start = Regex.scan(~r/\S+|\s+/, line)
  #   line = String.slice(line, String.length(start)..String.length(line))

  #   matches = patterns = [~r/\S+|\s+/, ~r/\S+|\s+/, ~r/\S+|\s+/]
  #   |> Enum.flat_map(&Regex.scan(&1, start))
  #   find_token(line, [matches | res])
  # end

@spec find_token(String.t()) :: list() #que es el spect
def find_token(line), do: find_token(line, [])

defp find_token("", res), do: Enum.reverse(res)
defp find_token(line, res) do
  #[[start]] = Regex.scan( ~r/^\S+|^\s+/, line)
  patterns = [
    {:reserved_word, ~r/^break\b|^try\b|^catch\b|^char\b|^class\b|^const\b|
    ^continue\b|^default\b|^delete\b|^auto\b|^else\b|^friend\b|^for\b|^float\b|
    ^long\b|^new\b|^operator\b|^private\b|^protected\b|^public\b|^return\b|^short\b|
    ^sizeof\b|^static\b|^this\b|^typedef\b|^enum\b|^throw\b|^mutable\b|^struct\b|^case\b|
    ^register\b|^switch\b|^and\b|^or\b|^namespace\b|^static_cast\b|^goto\b|^not\b|^xor\b|
    ^bool\b|^do\b|^double\b|^int\b|^unsigned\b|^void\b|^virtual\b|^union\b|^while\b|^std\b|^cout\b|^endl\b/}, #error de corte
    {:preprocessing, ~r/^#\w+/},
    {:library,  ~r/^[<"][\w\.]+[>"]/},
    {:newline, ~r/^\n+/},
    {:space, ~r/^\s/},
    {:special_symbol, ~r/^;/},
    {:structure_or_class_name, ~r/^\w+(?=\s*\{)/},
    {:structure_or_class_instance_declaration, ~r/^\w+\s+\w+/},
    {:structure_or_class_instance, ~r/^(?!\d)\w+(?=\.)/},
    {:curly_braces, ~r/^{|^}/},
    {:parenthesis, ~r/^\(|^\)/},
    {:function_name, ~r/^\w+(?=\s*\()/},
    {:integer_number, ~r/^[-+]?\d+\b(?!\.)/},
    {:float_number, ~r/^[+-]?\d*\.\d+/},
    {:operator, ~r/^\+(?!\+)|^\-(?!\-)|^\=(?!\=)|^\:(?!\:)|^\:\:|^\<(?!\<)|^\>(?!\>)|^\&(?!\&)|^\<\<|^\>\>|^\.|^\+\+|^\-\-|^\=\=|^\&\&|^\,/}, #checar si esto es valido, ver si pasando primero new line esta correcto, mult,div,per
    {:string, ~r/^".*"/},
    {:comment, ~r/^\/\/.*|\/\*[\s\S]*?\*\//},
    {:template_type, ~r/^\w+<\w+>/}, #cambiar a espacios
    {:variable, ~r/^\w+/}
  ]

  {token_type, token, remaining_line} =
    patterns
    |> Enum.find_value({nil, nil, line}, fn {type, pattern} ->
      case Regex.run(pattern, line, capture: :first) do
        [match] ->
          IO.inspect(String.length(match), label: 'longitud')
          IO.inspect(match, label: 'match')
          IO.inspect(type, label: 'Tipo')
          remaining = String.slice(line, String.length(match)..String.length(line))
          IO.inspect(remaining, label: 'Sobrante')
          {type, match, remaining}
        nil -> false
      end
    end)

  #new_res = if token_type == :space, do: res, else: [{token_type, token} | res]
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
# def doHtml(list, out_fd) do
#   IO.puts(out_fd, '<!DOCTYPE html>
#   <html lang="en">
#   <head>
#       <meta charset="UTF-8">
#       <meta name="viewport" content="width=device-width, initial-scale=1.0">
#       <link rel="stylesheet" href="styles.css">
#       <title>Document</title>
#   </head>
#   <body>')

#   Enum.map(list, fn {class, word} ->
#     cond do
#       class == :space -> IO.puts(out_fd, " ")
#       class == :newline -> IO.puts(out_fd, "\n")
#       true ->  IO.puts(out_fd, '<span class="#{class}">#{word}</span>')
#    end
#  end)

# #  Enum.map(list, fn {class, word} ->
# #   IO.puts(out_fd, '<span class="#{class}">#{word}</span>')
# #  end)

#   IO.puts(out_fd, '</body>
#   </html>')
# end

end

# IO.inspect(line, label: "Processing line")
#     Regex.scan(~r/#include/, line)

# Code to read a single command line argument
[in_filename] = System.argv()
# Create the name of the output file
# Add the string "-emails" before the file extension
out_filename = String.replace(in_filename, ~r/(\.\w+$)/, "-tokens.html")
# Call the function to find emails
Tfile.get_emails(in_filename, out_filename)

# Now the program can be called as:
# elixir 07_file_io.exs loren_emails.txt
