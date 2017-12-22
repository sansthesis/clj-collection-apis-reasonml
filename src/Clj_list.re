let first = (list) =>
  switch list {
  | [] => None
  | [a, ..._rest] => Some(a)
  };

let rest = (list) =>
  switch list {
  | [] => []
  | [_, ...rest] => rest
  };

let next = (list) =>
  switch list {
  | [] => None
  | [_] => None
  | [_, ...rest] => Some(rest)
  };

let cons = (item, list) => List.append([item], list);

/* O(n^2) runtime :-( https://github.com/jasonrose/clj-collection-apis-reasonml/issues/1 */
let distinct = (list) =>
  List.fold_left(
    (acc, item) =>
      if (List.mem(item, acc)) {
        acc
      } else {
        List.append(acc, [item])
      },
    [],
    list
  );

let rec remove = (predicate, list) =>
  switch list {
  | [] => []
  | [a] =>
    if (predicate(a)) {
      []
    } else {
      [a]
    }
  | [a, ...rest] =>
    if (predicate(a)) {
      remove(predicate, rest)
    } else {
      List.append([a], remove(predicate, rest))
    }
  };

let rec keep = (f, list) =>
  switch list {
  | [] => []
  | [a] =>
    switch (f(a)) {
    | Some(value) => [value]
    | None => []
    }
  | [a, ...rest] =>
    switch (f(a)) {
    | Some(value) => List.append([value], keep(f, rest))
    | None => keep(f, rest)
    }
  };

let rec interpose = (delimiter, list) =>
  switch list {
  | [] => []
  | [_] => list
  | [head, ...rest] =>
    List.append([head, delimiter], interpose(delimiter, rest))
  };

let rec drop = (n, list) =>
  switch (list, n) {
  | ([], _) => []
  | ([a], 0) => [a]
  | ([_], _) => []
  | ([_, ..._], 0) => list
  | ([_, ...rest], i) => drop(i - 1, rest)
  };

let rec dropWhile = (predicate, list) =>
  switch list {
  | [] => []
  | [a] =>
    if (predicate(a)) {
      []
    } else {
      [a]
    }
  | [a, ...rest] =>
    if (predicate(a)) {
      dropWhile(predicate, rest)
    } else {
      list
    }
  };

let rec take = (n, list) =>
  switch list {
  | [] => []
  | [a] =>
    if (n > 0) {
      [a]
    } else {
      []
    }
  | [a, ...rest] =>
    if (n > 0) {
      List.append([a], take(n - 1, rest))
    } else {
      []
    }
  };

let rec takeNthPrivate = (n, i, list) =>
  switch list {
  | [] => []
  | [a] =>
    if (i mod n == 0) {
      [a]
    } else {
      []
    }
  | [a, ...rest] =>
    if (i mod n == 0) {
      List.append([a], takeNthPrivate(n, i + 1, rest))
    } else {
      takeNthPrivate(n, i + 1, rest)
    }
  };

let takeNth = (n, list) => takeNthPrivate(n, 0, list);

let rec takeWhile = (predicate, list) =>
  switch list {
  | [] => []
  | [a] =>
    if (predicate(a)) {
      [a]
    } else {
      []
    }
  | [a, ...rest] =>
    if (predicate(a)) {
      List.append([a], takeWhile(predicate, rest))
    } else {
      []
    }
  };

let rec butLast = (list) =>
  switch list {
  | [] => None
  | [_] => None
  | [h, ...rest] =>
    let l = butLast(rest);
    switch l {
    | None => Some([h])
    | Some(remainder) => Some(List.append([h], remainder))
    }
  };

/*
 let dropLast = (n, list) => {
   let remainder = List.length(list) - n;
   if (remainder < 0) {
     []
   } else {
     List.sub(list, 0, remainder)
   }
 };
 */
let reverse = List.rev;

let splitAt = (index, list) => [take(index, list), drop(index, list)];

/* Can be optimized to not run over the list twice https://github.com/jasonrose/clj-collection-apis-reasonml/issues/2 */
let splitWith = (predicate, list) => [
  takeWhile(predicate, list),
  dropWhile(predicate, list)
];

let partition = (n, list) => {
  let (_, _, output) =
    List.fold_left(
      (acc, item) => {
        let (remainder, remainderSize, partitions) = acc;
        if (remainderSize == n - 1) {
          ([], 0, List.append(partitions, [List.append(remainder, [item])]))
        } else {
          (List.append(remainder, [item]), remainderSize + 1, partitions)
        }
      },
      ([], 0, []),
      list
    );
  output
};

let partitionAll = (n, list) => {
  let (remainder, partitions) =
    List.fold_left(
      (acc, item) =>
        if (acc |> fst |> List.length == n - 1) {
          ([], List.append(snd(acc), [List.append(fst(acc), [item])]))
        } else {
          (List.append(fst(acc), [item]), snd(acc))
        },
      ([], []),
      list
    );
  switch remainder {
  | [] => partitions
  | _ => List.append(partitions, [remainder])
  }
};

let partitionBy = (fn, list) =>
  switch list {
  | [] => []
  | [_, ..._] =>
    let (_, r, value) =
      List.fold_left(
        (acc, item) => {
          let (fnValue, remainder, partitions) = acc;
          let newFnValue = fn(item);
          if (fnValue == newFnValue) {
            (newFnValue, List.append(remainder, [item]), partitions)
          } else {
            (newFnValue, [item], List.append(partitions, [remainder]))
          }
        },
        (fn(List.hd(list)), [List.hd(list)], []),
        rest(list)
      );
    List.append(value, [r])
  };

let second = (list) =>
  switch list {
  | [] => None
  | [_] => None
  | [_, ...rest] => Some(List.hd(rest))
  };

let rec nth = (index, defaultValue, list) =>
  switch (list, index) {
  | ([], _) => defaultValue
  | ([a], 0) => a
  | ([_], _) => defaultValue
  | ([a, ..._], 0) => a
  | ([_, ...rest], n) => nth(n - 1, defaultValue, rest)
  };

let rec last = (list) =>
  switch list {
  | [] => None
  | [a] => Some(a)
  | [_, ...rest] => last(rest)
  };

let notEmpty = (list) =>
  switch list {
  | [] => None
  | _ => Some(list)
  };

let some = (predicate, list) =>
  List.fold_left(
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
  List.fold_left((acc, item) => acc && predicate(item), true, list);

let notEvery = (predicate, list) => ! every(predicate, list);

let notAny = (predicate, list) =>
  switch (some(predicate, list)) {
  | None => true
  | Some(_) => false
  };

let empty = (list) =>
  switch list {
  | [] => true
  | _ => false
  };

let rec repeatedly = (n, fn) =>
  if (n <= 0) {
    []
  } else {
    List.append([fn()], repeatedly(n - 1, fn))
  };

let rec repeat = (n, value) =>
  if (n <= 0) {
    []
  } else {
    List.append([value], repeat(n - 1, value))
  };

let rec range = (start, _end) =>
  if (start >= _end) {
    []
  } else {
    List.append([start], range(start + 1, _end))
  };

let dedupe = (list) =>
  switch list {
  | [] => []
  | [a] => [a]
  | [a, ...rest] =>
    let (lastItemInArray, itemLastInserted, arr) =
      List.fold_left(
        (acc, item) => {
          let (current, _, arr) = acc;
          if (current == item) {
            acc
          } else {
            (item, current, List.append(arr, [current]))
          }
        },
        (a, a, []),
        rest
      );
    if (lastItemInArray == itemLastInserted) {
      arr
    } else {
      List.append(arr, [lastItemInArray])
    }
  };

let conj = (list, item) =>
  switch list {
  | None => [item]
  | Some(l) => List.append([item], l)
  };

let rec contains = (list, index) =>
  switch (list, index) {
  | ([], _) => false
  | ([_], 0) => true
  | ([_], _) => false
  | ([_, ..._], 0) => true
  | ([_, ...rest], n) => contains(rest, n - 1)
  };
