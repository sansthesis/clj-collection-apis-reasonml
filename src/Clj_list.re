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

let rec distinctPrivate = (cache, list) =>
  switch list {
  | [] => []
  | [a] =>
    if (List.mem(a, cache)) {
      []
    } else {
      [a]
    }
  | [a, ...rest] =>
    if (List.mem(a, cache)) {
      distinctPrivate(cache, rest)
    } else {
      List.append([a], distinctPrivate(List.append([a], cache), rest))
    }
  };

/* O(n^2) runtime :-( https://github.com/jasonrose/clj-collection-apis-reasonml/issues/1 */
let distinct = (list) => distinctPrivate([], list);

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

let rec dropLastPrivate = (n, list) =>
  switch list {
  | [] => (n, [])
  | [a] =>
    if (n == 0) {
      (0, [a])
    } else {
      (n - 1, [])
    }
  | [a, ...rest] =>
    let (i, l) = dropLastPrivate(n, rest);
    if (i == 0) {
      (0, List.append([a], l))
    } else {
      (i - 1, [])
    }
  };

let dropLast = (n, list) => dropLastPrivate(n, list) |> snd;

let reverse = List.rev;

let splitAt = (index, list) => [take(index, list), drop(index, list)];

let rec splitWithPrivate = (predicate, list) =>
  switch list {
  | [] => ([], [])
  | [a] =>
    if (predicate(a)) {
      ([a], [])
    } else {
      ([], [a])
    }
  | [a, ...rest] =>
    if (predicate(a)) {
      let (takeL, dropL) = splitWithPrivate(predicate, rest);
      (List.append([a], takeL), dropL)
    } else {
      ([], list)
    }
  };

/* Can be optimized to not run over the list twice https://github.com/jasonrose/clj-collection-apis-reasonml/issues/2 */
let splitWith = (predicate, list) => {
  let (t, d) = splitWithPrivate(predicate, list);
  [t, d]
};

let rec partitionPrivate = (n, i, list) =>
  switch list {
  | [] => []
  | [a] =>
    if (i mod n == 0) {
      [[a]]
    } else {
      []
    }
  | [a, ...rest] =>
    let tmp = partitionPrivate(n, i + 1, rest);
    switch tmp {
    | [] =>
      if (i mod n == 0) {
        [[a]]
      } else {
        []
      }
    | [b, ...rem] =>
      if (i mod n == 0) {
        List.append([[a]], tmp)
      } else {
        List.append([List.append([a], b)], rem)
      }
    }
  };

let partition = (n, list) => partitionPrivate(n, 1, list);

let rec partitionAllPrivate = (n, i, list) =>
  switch list {
  | [] => []
  | [a] => [[a]]
  | [a, ...rest] =>
    let tmp = partitionAllPrivate(n, i + 1, rest);
    switch tmp {
    | [] => [[a]]
    | [b, ...rem] =>
      if (i mod n == 0) {
        List.append([[a]], tmp)
      } else {
        List.append([List.append([a], b)], rem)
      }
    }
  };

let partitionAll = (n, list) => partitionAllPrivate(n, 1, list);

let rec partitionBy = (fn, list) =>
  switch list {
  | [] => []
  | [a] => [[a]]
  | [a, ...rest] =>
    let tmp = partitionBy(fn, rest);
    switch tmp {
    | [] => [[a]]
    | [b, ...rem] =>
      if (fn(a) == fn(List.hd(b))) {
        List.append([List.append([a], b)], rem)
      } else {
        List.append([[a]], tmp)
      }
    }
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

let rec some = (predicate, list) =>
  switch list {
  | [] => None
  | [a] =>
    if (predicate(a)) {
      Some(a)
    } else {
      None
    }
  | [a, ...rest] =>
    if (predicate(a)) {
      Some(a)
    } else {
      some(predicate, rest)
    }
  };

let rec every = (predicate, list) =>
  switch list {
  | [] => true
  | [a] => predicate(a)
  | [a, ...rest] => predicate(a) && every(predicate, rest)
  };

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

let rec dedupe = (list) =>
  switch list {
  | [] => []
  | [a] => [a]
  | [a, ...rest] =>
    let next = dedupe(rest);
    if (a == List.hd(next)) {
      next
    } else {
      List.append([a], next)
    }
  };

let conj = (list, item) => List.append([item], list);

let rec contains = (list, index) =>
  switch (list, index) {
  | ([], _) => false
  | ([_], 0) => true
  | ([_], _) => false
  | ([_, ..._], 0) => true
  | ([_, ...rest], n) => contains(rest, n - 1)
  };
