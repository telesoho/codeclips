# do something befor request

```javascript
private renderSwaggerUi(url: string, authenticationToken: string) {
    console.log('[Swagger] render swagger ui for ' + url);
    new SwaggerUi({
        dom_id: '#swagger-ui',
        url: url,
        spec: '',
        presets: [presets.apis],
        requestInterceptor:
            function (request) {
                console.log('[Swagger] intercept try-it-out request');
                request.headers.Authorization = authenticationToken;
                return request;
            }
    });
}
```
