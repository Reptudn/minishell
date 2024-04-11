# Minishell Tests

## Mandatory

## May be/is a problem regarding the eval(s)

- (echo '$USER' must print "$USER") -> prints user can be hardcoded i guess
- (🟢 minishell ➜ cd cd: (null): Bad address) -> go to root if cmd[0] == NULL
- (Unset the $PATH and ensure commands are not working anymore) -> seems like its not working
- ('cat | cat | ls' should behave in a "normal way") -> it does not

- (split with brackets) -> need to take a look into that problem

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