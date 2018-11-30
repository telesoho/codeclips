# Use composer to run tests in laravel
DONT use global phpunit, But use composer command:
```sh
composer autodumpload
composer run test
composer run test -- --filter MyTest
```
