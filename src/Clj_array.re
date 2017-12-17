let first = (array) =>
  switch (Array.length(array)) {
  | 0 => None
  | _ => Some(array[0])
  };

let rest = (array) =>
  switch (Array.length(array)) {
  | 0 => [||]
  | 1 => [||]
  | _ => Array.sub(array, 1, Array.length(array) - 1)
  };

let next = (array) =>
  switch (Array.length(array)) {
  | 0 => None
  | 1 => None
  | _ => Some(Array.sub(array, 1, Array.length(array) - 1))
  };

let cons = (item, array) => Array.append([|item|], array);

let filter = (predicate, array) =>
  Array.fold_left(
    (acc, item) =>
      if (predicate(item)) {
        Array.append(acc, [|item|])
      } else {
        acc
      },
    [||],
    array
  );

/* O(n^2) runtime :-( https://github.com/jasonrose/clj-collection-apis-reasonml/issues/1 */
let distinct = (array) => {
  let arrayContains = (item, array) =>
    Array.fold_left((acc, x) => acc || x == item, false, array);
  Array.fold_left(
    (acc, item) =>
      if (arrayContains(item, acc)) {
        acc
      } else {
        Array.append(acc, [|item|])
      },
    [||],
    array
  )
};

let remove = (predicate, array) =>
  Array.fold_left(
    (acc, item) =>
      if (predicate(item)) {
        acc
      } else {
        Array.append(acc, [|item|])
      },
    [||],
    array
  );

let keep = (f, array) =>
  Array.fold_left(
    (acc, item) =>
      switch (f(item)) {
      | Some(value) => Array.append(acc, [|value|])
      | None => acc
      },
    [||],
    array
  );

let interpose = (delimiter, array) =>
  switch (Array.length(array)) {
  | 0 => [||]
  | 1 => array
  | _ =>
    let fencepost =
      Array.fold_left(
        (acc, item) => Array.append(acc, [|item, delimiter|]),
        [||],
        array
      );
    Array.sub(fencepost, 0, Array.length(fencepost) - 1)
  };

let drop = (n, array) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) > 0) {
        (fst(acc) - 1, snd(acc))
      } else {
        (0, Array.append(snd(acc), [|item|]))
      },
    (n, [||]),
    array
  )
  |> snd;

let dropWhile = (predicate, array) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) && predicate(item)) {
        (fst(acc), snd(acc))
      } else {
        (false, Array.append(snd(acc), [|item|]))
      },
    (true, [||]),
    array
  )
  |> snd;

let take = (n, array) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) > 0) {
        (fst(acc) - 1, Array.append(snd(acc), [|item|]))
      } else {
        (0, snd(acc))
      },
    (n, [||]),
    array
  )
  |> snd;

let takeNth = (n, array) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) mod n == 0) {
        (fst(acc) + 1, Array.append(snd(acc), [|item|]))
      } else {
        (fst(acc) + 1, snd(acc))
      },
    (n, [||]),
    array
  )
  |> snd;

let takeWhile = (predicate, array) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) && predicate(item)) {
        (true, Array.append(snd(acc), [|item|]))
      } else {
        (false, snd(acc))
      },
    (true, [||]),
    array
  )
  |> snd;

let butLast = (array) =>
  switch (Array.length(array)) {
  | 0 => None
  | 1 => None
  | _ => Some(Array.sub(array, 0, Array.length(array) - 1))
  };

let dropLast = (n, array) => {
  let remainder = Array.length(array) - n;
  if (remainder < 0) {
    [||]
  } else {
    Array.sub(array, 0, remainder)
  }
};

let reverse = (array) => {
  let length = Array.length(array) - 1;
  if (length > 0) {
    for (i in 0 to length / 2) {
      let swap = array[length - i];
      array[length - i] = array[i];
      array[i] = swap
    };
    array
  } else {
    array
  }
};

let splitAt = (index, array) => [|take(index, array), drop(index, array)|];

let splitWith = (predicate, array) => [|
  takeWhile(predicate, array),
  dropWhile(predicate, array)
|];

let partition = (n, array) =>
  if (n > Array.length(array)) {
    [||]
  } else {
    Array.fold_left(
      (acc, item) =>
        if (acc |> fst |> Array.length == n - 1) {
          ([||], Array.append(snd(acc), [|Array.append(fst(acc), [|item|])|]))
        } else {
          (Array.append(fst(acc), [|item|]), snd(acc))
        },
      ([||], [||]),
      array
    )
    |> snd
  };

let partitionAll = (n, array) => {
  let (remainder, partitions) =
    Array.fold_left(
      (acc, item) =>
        if (acc |> fst |> Array.length == n - 1) {
          ([||], Array.append(snd(acc), [|Array.append(fst(acc), [|item|])|]))
        } else {
          (Array.append(fst(acc), [|item|]), snd(acc))
        },
      ([||], [||]),
      array
    );
  if (Array.length(remainder) > 0) {
    Array.append(partitions, [|remainder|])
  } else {
    partitions
  }
};

let partitionBy = (fn, array) =>
  if (Array.length(array) == 0) {
    [||]
  } else {
    let (_, r, value) =
      Array.fold_left(
        (acc, item) => {
          let (fnValue, remainder, partitions) = acc;
          let newFnValue = fn(item);
          if (fnValue == newFnValue) {
            (newFnValue, Array.append(remainder, [|item|]), partitions)
          } else {
            (newFnValue, [|item|], Array.append(partitions, [|remainder|]))
          }
        },
        (fn(array[0]), [|array[0]|], [||]),
        rest(array)
      );
    Array.append(value, [|r|])
  };

let second = (array) =>
  if (Array.length(array) < 2) {
    None
  } else {
    Some(array[1])
  };

let nth = (index, defaultValue, array) =>
  if (index >= 0 && index < Array.length(array)) {
    array[index]
  } else {
    defaultValue
  };

let last = (array) =>
  if (Array.length(array) == 0) {
    None
  } else {
    Some(array[Array.length(array) - 1])
  };

let notEmpty = (array) =>
  if (Array.length(array) == 0) {
    None
  } else {
    Some(array)
  };

let some = (predicate, array) =>
  Array.fold_left(
    (acc, item) =>
      switch acc {
      | Some(x) => Some(x)
      | None =>
        if (predicate(item)) {
          Some(item)
        } else {
          None
        }
      },
    None,
    array
  );

let every = (predicate, array) =>
  Array.fold_left((acc, item) => acc && predicate(item), true, array);

let notEvery = (predicate, array) => ! every(predicate, array);

let notAny = (predicate, array) =>
  switch (some(predicate, array)) {
  | None => true
  | Some(_) => false
  };

let empty = (array) => Array.length(array) == 0;

let repeatedly = (n, fn) => Array.init(n, (_) => fn());
