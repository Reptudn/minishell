# Minishell Tests

## Mandatory

## May be/is a problem regarding the eval(s)

- ('cat | cat | ls' should behave in a "normal way") -> it does not


### Builtins
#### Echo
- [] echo hello world
- [] echo "hello world"
- [] echo 'hello world'
- [] echo hello'world'
- [] echo hello""world
- [] echo ''
- [] echo "$PWD"
- [] echo '$PWD'
- [] echo "aspas ->'"
- [] echo "aspas -> ' "
- [] echo 'aspas ->"'
- [] echo 'aspas -> " '

## Bonus