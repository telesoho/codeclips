# Solve laravel passport CORS
https://medium.com/@mshanak/solved-laravel-5-3-passport-with-cors-2c6667ef058b

## install laravel-cors

https://github.com/barryvdh/laravel-cors

## setup laravel for laravel-cors.

Registe cors middleware.

```php
    // file: App/Http/Kernel.php
    protected $routeMiddleware = [
        ...
        'cors' => \Barryvdh\Cors\HandleCors::class,
    ];
```

Add cors to Passport routes:

```php
    // file:  app/Providers/AuthServiceProvider.php
    public function boot()
    {
        $this->registerPolicies();

        // 注册Passport路由
        Passport::routes(null, [
            'middleware' => ['cors']
        ]);

        // 设定Passport作用域
        Passport::tokensCan([
            'customer' => '普通用户',
            'salesman' => '卖手'
        ]);
    }
```
