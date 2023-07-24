# Read the file
with open('./snippets/file.txt', 'r') as f:
    content = f.read()

# Replace ']' with '],' and handle the edge cases
content = content.replace('] ]', '], ]').replace('] ]]', '], ]]').replace(']\n', '],\n')

# Write the modified content back to the file
with open('./snippets/file.txt', 'w') as f:
    f.write(content)


    