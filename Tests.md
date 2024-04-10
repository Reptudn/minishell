# Minishell Tests

## Mandatory

## May be/is a problem regarding the eval(s)
- (Check the global variable. This global variable cannot provide any other information or data access than the number of a received signal.) -> might be a problem cause we use a boolen
- (Test only spaces or tabs.) -> we get a similar output like ls or ls -la
- (Try ctrl-C after running a blocking command like cat without arguments or grep “something“) -> we get minishell twice like this: 🟢 minishell ➜ 🟢 minishell ➜ 
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