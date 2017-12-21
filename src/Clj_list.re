let first = (list) =>
  switch list {
  | [] => None
  | [a, ..._rest] => Some(a)
  };

let rest = (list) =>
  switch (Array.length(list)) {
  | 0 => [||]
  | 1 => [||]
  | _ => Array.sub(list, 1, Array.length(list) - 1)
  };

let next = (list) =>
  switch (Array.length(list)) {
  | 0 => None
  | 1 => None
  | _ => Some(Array.sub(list, 1, Array.length(list) - 1))
  };

let cons = (item, list) => Array.append([|item|], list);

let filter = (predicate, list) =>
  Array.fold_left(
    (acc, item) =>
      if (predicate(item)) {
        Array.append(acc, [|item|])
      } else {
        acc
      },
    [||],
    list
  );

/* O(n^2) runtime :-( https://github.com/jasonrose/clj-collection-apis-reasonml/issues/1 */
let distinct = (list) => {
  let listContains = (item, list) =>
    Array.fold_left((acc, x) => acc || x == item, false, list);
  Array.fold_left(
    (acc, item) =>
      if (listContains(item, acc)) {
        acc
      } else {
        Array.append(acc, [|item|])
      },
    [||],
    list
  )
};

let remove = (predicate, list) =>
  Array.fold_left(
    (acc, item) =>
      if (predicate(item)) {
        acc
      } else {
        Array.append(acc, [|item|])
      },
    [||],
    list
  );

let keep = (f, list) =>
  Array.fold_left(
    (acc, item) =>
      switch (f(item)) {
      | Some(value) => Array.append(acc, [|value|])
      | None => acc
      },
    [||],
    list
  );

let interpose = (delimiter, list) =>
  switch (Array.length(list)) {
  | 0 => [||]
  | 1 => list
  | _ =>
    let fencepost =
      Array.fold_left(
        (acc, item) => Array.append(acc, [|item, delimiter|]),
        [||],
        list
      );
    Array.sub(fencepost, 0, Array.length(fencepost) - 1)
  };

let drop = (n, list) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) > 0) {
        (fst(acc) - 1, snd(acc))
      } else {
        (0, Array.append(snd(acc), [|item|]))
      },
    (n, [||]),
    list
  )
  |> snd;

let dropWhile = (predicate, list) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) && predicate(item)) {
        (fst(acc), snd(acc))
      } else {
        (false, Array.append(snd(acc), [|item|]))
      },
    (true, [||]),
    list
  )
  |> snd;

let take = (n, list) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) > 0) {
        (fst(acc) - 1, Array.append(snd(acc), [|item|]))
      } else {
        (0, snd(acc))
      },
    (n, [||]),
    list
  )
  |> snd;

let takeNth = (n, list) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) mod n == 0) {
        (fst(acc) + 1, Array.append(snd(acc), [|item|]))
      } else {
        (fst(acc) + 1, snd(acc))
      },
    (n, [||]),
    list
  )
  |> snd;

let takeWhile = (predicate, list) =>
  Array.fold_left(
    (acc, item) =>
      if (fst(acc) && predicate(item)) {
        (true, Array.append(snd(acc), [|item|]))
      } else {
        (false, snd(acc))
      },
    (true, [||]),
    list
  )
  |> snd;

let butLast = (list) =>
  switch (Array.length(list)) {
  | 0 => None
  | 1 => None
  | _ => Some(Array.sub(list, 0, Array.length(list) - 1))
  };

let dropLast = (n, list) => {
  let remainder = Array.length(list) - n;
  if (remainder < 0) {
    [||]
  } else {
    Array.sub(list, 0, remainder)
  }
};

let reverse = (list) => {
  let length = Array.length(list) - 1;
  if (length > 0) {
    for (i in 0 to length / 2) {
      let swap = list[length - i];
      list[length - i] = list[i];
      list[i] = swap
    };
    list
  } else {
    list
  }
};

let splitAt = (index, list) => [|take(index, list), drop(index, list)|];

let splitWith = (predicate, list) => [|
  takeWhile(predicate, list),
  dropWhile(predicate, list)
|];

let partition = (n, list) =>
  if (n > Array.length(list)) {
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
      list
    )
    |> snd
  };

let partitionAll = (n, list) => {
  let (remainder, partitions) =
    Array.fold_left(
      (acc, item) =>
        if (acc |> fst |> Array.length == n - 1) {
          ([||], Array.append(snd(acc), [|Array.append(fst(acc), [|item|])|]))
        } else {
          (Array.append(fst(acc), [|item|]), snd(acc))
        },
      ([||], [||]),
      list
    );
  if (Array.length(remainder) > 0) {
    Array.append(partitions, [|remainder|])
  } else {
    partitions
  }
};

let partitionBy = (fn, list) =>
  if (Array.length(list) == 0) {
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
        (fn(list[0]), [|list[0]|], [||]),
        rest(list)
      );
    Array.append(value, [|r|])
  };

let second = (list) =>
  if (Array.length(list) < 2) {
    None
  } else {
    Some(list[1])
  };

let nth = (index, defaultValue, list) =>
  if (index >= 0 && index < Array.length(list)) {
    list[index]
  } else {
    defaultValue
  };

let last = (list) =>
  if (Array.length(list) == 0) {
    None
  } else {
    Some(list[Array.length(list) - 1])
  };

let notEmpty = (list) =>
  if (Array.length(list) == 0) {
    None
  } else {
    Some(list)
  };

let some = (predicate, list) =>
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
    list
  );

let every = (predicate, list) =>
  Array.fold_left((acc, item) => acc && predicate(item), true, list);

let notEvery = (predicate, list) => ! every(predicate, list);

let notAny = (predicate, list) =>
  switch (some(predicate, list)) {
  | None => true
  | Some(_) => false
  };

let empty = (list) => Array.length(list) == 0;

let repeatedly = (n, fn) => Array.init(n, (_) => fn());

let repeat = (n, value) => Array.init(n, (_) => value);

let rec range = (start, _end) =>
  if (start >= _end) {
    [||]
  } else {
    Array.append([|start|], range(start + 1, _end))
  };

let dedupe = (list) =>
  if (Array.length(list) == 0) {
    [||]
  } else {
    let (lastItemInArray, itemLastInserted, arr) =
      Array.fold_left(
        (acc, item) => {
          let (current, _, arr) = acc;
          if (current == item) {
            acc
          } else {
            (item, current, Array.append(arr, [|current|]))
          }
        },
        (list[0], list[0], [||]),
        list
      );
    if (lastItemInArray == itemLastInserted) {
      arr
    } else {
      Array.append(arr, [|lastItemInArray|])
    }
  };

let conj = (list, item) =>
  switch list {
  | None => [|item|]
  | Some(arr) => Array.append(arr, [|item|])
  };

let contains = (list, index) => index >= 0 && index < Array.length(list);
