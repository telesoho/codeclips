
## ERROR

Unable to preventDefault inside passive event listener due to target being treated as passive.

https://github.com/bevacqua/dragula/issues/468

## solution

use css rule

```css
#slider {
  touch-action: none;
}
```
