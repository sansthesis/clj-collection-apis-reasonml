# Clojure Collection APIs in Reason

This project aims to implement the Clojure collection APIs for Reason's Array and List types whenever they make sense.

Reference the unit tests for examples on usage.


## Using clj-collection-apis-reasonml

First, add the dependency to your `package.json`:
```
yarn add clj-collection-apis-reasonml
```

Then add it to your `bsconfig.json`:
```
"bs-dependencies": [
  "clj-collection-apis-reasonml"
],
```

Finally, you're free to use it in your code:

```
/* test.re */
let myVal = Clj.Array.drop(2, [|1, 2, 3|]);
/* myVal is now [|3|] */
```

## [API Reference](https://github.com/jasonrose/clj-collection-apis-reasonml/blob/master/API.md)
