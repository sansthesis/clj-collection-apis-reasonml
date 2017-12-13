module Array = {
  let first = (array) =>
    switch (Array.length(array)) {
    | 0 => None
    | _ => Some(array[0])
    };
  let rest = (array) =>
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
  /*let distinct = (array) => [||];*/
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
};
