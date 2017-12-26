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

## API Reference

`Clj.Array` and `Clj.List` have the same APIs in almost every case.  The only exceptions are when a function already exists in the standard lib with the same name, parameters, and semantics.

### [first](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/first)
Returns the first element of the array or list, or `None` if the array or list is empty.

### [rest](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/rest)
Returns an empty array or list for an array or list with 0 or 1 elements, or an array or list of every element after the first if given an array or list of length greater than one.

### [next](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/next)
Returns `None` for an array or list with 0 or 1 elements, or an array or list of every element after the first if given an array or list of length greater than one.

### [cons](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/cons)
Adds an element to the beginning of an array or list.

### [filter](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/filter)
Returns an array or list of every element `e` where `predicate(e)` returns `true`.

### [distinct](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/distinct)
Returns an array or list of every element that appears in the source array or list without including duplicates.

### [remove](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/remove)
Returns an array or list of every element `e` where `predicate(e)` returns `false`.

### [keep](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/keep)
Returns an array or list of every element `e` where `f(e)` returns `Some`.

### [interpose](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/interpose)
Returns an array or list with `delimiter` inserted between every element in the source array or list.

### [drop](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/drop)
Returns an array or list without the first `n` elements present.  Returns an empty array or list if `n` is greater than the length of the array or list.

### [dropWhile](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/drop-while)
Returns an array or list starting at the first element `e` in the source array or list where `predicate(e)` returns `false`.

### [take](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/take)
Returns an array or list of the first `n` elements in the source array or list.

### [takeNth](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/take-nth)
Returns an array or list of every `n`th item in the source array or list.

### [takeWhile](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/take-while)
Returns an array or list from the beginning of the source array or list to the first element `e` where `predicate(e)` returns `false`.

### [butLast](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/butlast)
Returns an array or list of every element in the source array or list except for the very last.  Returns `None` for an array or list of length 0 or 1.

### [dropLast](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/drop-last)
Returns an array or list of every element in the source array or list except for the `n` last elements.  Returns an empty array or list if `n` is greater than the length of the source array or list.

### [reverse](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/reverse)
Returns an array or list in reverse order of the source array or list.

### [splitAt](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/split-at)
Returns a two-element array or list where the first array or list is every element before `index` and the second array or list is every element after `index`.

### [partition](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/partition)
Splits the source array or list into an array or list of array or lists of size `n`.  If the final partition's size is smaller than `n`, it is not included in the output.

### [partitionAll](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/partition-all)
Splits the source array or list into an array or list of array or lists of size `n`.  If the final partition's size is smaller than `n`, it is still included in the output.

### [partitionBy](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/partition-by)
Splits the source array or list into an array or list of arrays or lists.  Each partition in the array or list is composed of elements `e` where `fn(e)` returns the same value.  Once that value changes, it starts a new partition.

### [second](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/second)
Returns the second element in the source array or list, or `None` if the array or list is not at least 2 elements long.

### [nth](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/nth)
Returns the element at index `n` in the array or list.  Returns `defaultValue` if `index` is not in bounds of the array or list.

### [last](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/last)
Returns the last element in the array or list.  Returns `None` if the array or list is empty.

### [notEmpty](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/not-empty)
Returns `None` if the array or list is empty.  Returns the input array or list if it is not empty.

### [some](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/some)
Returns the first element `e` in the array or list for which `predicate(e)` returns `true`.  Returns `None` if `predicate(e)` is `false` for every element in the array or list.

### [every](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/every?)
Returns `true` if `predicate(e)` returns `true` for every element `e` in the array or list.  Returns `true` if the array or list is empty.

### [notEvery](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/not-every?)
Returns `true` if `predicate(e)` returns `false` for at least one element `e` in the array or list. Returns `false` if the array or list is empty.

### [empty](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/empty?)
Returns `true` if the array or list has zero elements.  Returns `false` if the array or list has at least one element.

### [repeatedly](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/repeatedly)
Creates an array or list of length `n` where every element is initialized to the output of `fn()`.

### [repeat](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/repeat)
Creates an array or list of length `n` where every element is initialized to `value`.

### [range](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/range)
Creates an array or list of integers of length `end - start` where the first value is `start` and increments by `1` until `end`.

### [dedupe](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/dedupe)
Returns an array or list with all consecutive duplicate values removed.  Non-consecutive duplicates will not be removed.

### [conj](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/conj)
Adds an element to the end of the source array.  Adds an element to the start of the source list.

### [contains](https://clojure.github.io/clojure/clojure.core-api.html#clojure.core/contains?)
Returns `true` if `index` is within the bounds of the source array or list.  Otherwise returns `false`.
