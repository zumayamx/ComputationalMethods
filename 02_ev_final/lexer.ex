# Lexer for C++ code
# José Manuel García Zumaya
# A01784238

# This program defines functions for tokenizing a line of text.
# It uses regular expressions to identify and classify different types of tokens
# such as reserved words, preprocessing directives, library references, and more.
# This program includes two ways to make the tokenization process, syncronous and asynchronous.

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
# Public function to find tokens in a line of text, initializing with an empty result list
def find_token(line), do: find_token(line, [])

# Private function clause to handle the base case when the line is empty
defp find_token("", res), do: Enum.reverse(res)

defp find_token(line, res) do
  # Define the patterns to match different types of tokens
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
    {:operator, ~r/^\+(?!\+)|^\-(?!\-)|^\=(?!\=)|^\:(?!\:)|^\:\:|^\<(?!\<)|^\>(?!\>)|^\&(?!\&)|^\<\<|^\>\>|^\.|^\+\+|^\-\-|^\=\=|^\&\&|^\,|^\[|^\]|^\!\=|^\*|^\-\>|^\//},
    {:string, ~r/^".*"/},
    {:comment, ~r/\/\/.*|\/\*[\s\S]*?\*\//},
    {:variable, ~r/^\w+/}
  ]

  # Find the first pattern that matches the start of the line
  {token_type, token, remaining_line} =
    patterns
      |> Enum.find_value({nil, nil, line}, fn {type, pattern} ->
        # Check if the pattern matches the line
        case Regex.run(pattern, line, capture: :first) do
          # If a match is found, extract the matched token and the remaining line
          [match] ->
            #IO.inspect(match, label: "Match")
            #IO.inspect(type, label: "Type")
            remaining = String.slice(line, String.length(match)..String.length(line))
            #IO.inspect()
            {type, match, remaining}
          # If no match is found, return false to continue checking other patterns
          nil -> false
        end
      end)

  # Recursively process the remaining line, accumulating the found tokens
  find_token(remaining_line, [{token_type, token} | res])
end

def doHtml(list, out_fd) do
  # Print the HTML document header
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

  # Process each element of the list and convert to HTML escaped strings wrapped in <span> tags according to their class
  html_content =
    Enum.map(list, fn {class, word} ->
      # Convert the element 'word' to a string
      word = to_string(word)

      # Replace special characters to escape HTML
      escaped_word = String.replace(word, "<", "&lt;")
                     |> String.replace(">", "&gt;")

      # Generate HTML content based on the element's class
      cond do
        # If the class is :space, simply add a space
        class == :space -> " "
        # If the class is :newline, add a newline character
        class == :newline -> "\n"
        # If the class is :library, wrap the content in a <span> with class 'library'
        class == :library -> "<span class=\"#{class}\">#{escaped_word}</span>"
        # For any other class, wrap the content in a <span> with the corresponding class
        true ->  "<span class=\"#{class}\">#{escaped_word}</span>"
      end
    end)

    # Join all elements into a single string
    |> Enum.join("")
    # Write the processed HTML content to the output file
    IO.puts(out_fd, html_content)
    # Write the closing HTML tags
    IO.puts(out_fd, """
    </code></pre>
    </body>
    </html>
    """)
  end

  # Function to procces the tokens in an async way
  # Using a default value for the number of threads to use
  def async_lexer(path, num_threads) do
    {time, _result} = :timer.tc(fn ->
    # Get the .cpp files in path
    files = File.ls!(path) |> Enum.filter(&String.ends_with?(&1, ".cpp"))

    # Calculate the size of each chunk
    chunk_size = div(length(files), num_threads)
    # Divide the files into chunks, one for each thread
    # .chuk_every:
    # Parameters:
    # 1. The list to split
    # 2. The size of the chunks
    # 3. The step size
    # 4. The extra value to add into each chunk
    # # Returns a list with sublists of chunks
    file_chunks = Enum.chunk_every(files, chunk_size, chunk_size, [])

    # Start a task for each chunk of files
    tasks = Enum.map(file_chunks, fn file_chunk ->
      Task.async(fn -> process_files(file_chunk) end)
    end)

    # Await the results of each task, with a timeout of infinity
    Enum.map(tasks, &Task.await(&1, :infinity))
    end)

    IO.puts("Time: #{time / 1_000_000} seconds" )
  end

  # Function to process a list of files
  defp process_files(files) do
    Enum.each(files, fn file_in ->
      # Generate the output filename
      file_out = String.replace(file_in, ~r/(\.\w+$)/, "-tokens.html")
      get_tokens(file_in, file_out)
    end)
  end

  # Function to process the tokens in a sync way
  def sync_lexer(path) do
    # Start the timer
    {time, _result} = :timer.tc(fn ->
    File.ls!(path) |> Enum.filter(&String.ends_with?(&1, ".cpp"))
    |> Enum.each(fn file_in ->
      # Generate the output filename
      file_out = String.replace(file_in, ~r/(\.\w+$)/, "-tokens.html")
      get_tokens(file_in, file_out)
      end)
    end)

    IO.puts("Time: #{time / 1_000_000} seconds" )
  end



end

# Code to read the command line arguments
[mode, path | rest] = System.argv()

# Determine the number of threads if provided, default to 4 if not
num_threads =
  if length(rest) > 0 do
    String.to_integer(hd(rest))
  else
    System.schedulers
  end

# Call the appropriate function based on the mode
case mode do
  "async" -> Tfile.async_lexer(path, num_threads)
  "sync" -> Tfile.sync_lexer(path)
  _ -> IO.puts("Invalid mode. Use 'async' or 'sync'.")
end

# Now the program can be called in two ways:
# elixir lexer.ex async /Users/josezumayamx/Documents/cppFiles 4
# elixir lexer.ex sync /Users/josezumayamx/Documents/cppFiles
