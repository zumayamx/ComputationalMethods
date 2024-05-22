# En un archivo o en el shell iex
result = Regex.scan(~r/^\&(?!\&)/, "&")
IO.inspect(result)
