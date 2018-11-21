# Creating Your Own PHP Helper Functions In Laravel
https://tutsforweb.com/creating-helpers-laravel/

If you do not use the namespace declaration, these functions will become globally available and you can use them without even specifying the namespace. All the Laravel built-in helper functions are defined without a namespace. 
```php
// namespace App\Helpers; 
/**
 *

if (!function_exists('human_file_size')) {
    function human_file_size($bytes, $decimals = 2)
    {
        // ...
    }
}
```
