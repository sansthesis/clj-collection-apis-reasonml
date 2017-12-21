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

let remove = (predicate, list) =>
  List.fold_left(
    (acc, item) =>
      if (predicate(item)) {
        acc
      } else {
        List.append(acc, [item])
      },
    [],
    list
  );

let keep = (f, list) =>
  List.fold_left(
    (acc, item) =>
      switch (f(item)) {
      | Some(value) => List.append(acc, [value])
      | None => acc
      },
    [],
    list
  );

let rec interpose = (delimiter, list) =>
  switch list {
  | [] => []
  | [_] => list
  | [head, ...rest] =>
    List.append([head, delimiter], interpose(delimiter, rest))
  };

let drop = (n, list) =>
  List.fold_left(
    (acc, item) =>
      if (fst(acc) > 0) {
        (fst(acc) - 1, snd(acc))
      } else {
        (0, List.append(snd(acc), [item]))
      },
    (n, []),
    list
  )
  |> snd;

let dropWhile = (predicate, list) =>
  List.fold_left(
    (acc, item) =>
      if (fst(acc) && predicate(item)) {
        (fst(acc), snd(acc))
      } else {
        (false, List.append(snd(acc), [item]))
      },
    (true, []),
    list
  )
  |> snd;

let take = (n, list) =>
  List.fold_left(
    (acc, item) =>
      if (fst(acc) > 0) {
        (fst(acc) - 1, List.append(snd(acc), [item]))
      } else {
        (0, snd(acc))
      },
    (n, []),
    list
  )
  |> snd;

let takeNth = (n, list) =>
  List.fold_left(
    (acc, item) =>
      if (fst(acc) mod n == 0) {
        (fst(acc) + 1, List.append(snd(acc), [item]))
      } else {
        (fst(acc) + 1, snd(acc))
      },
    (n, []),
    list
  )
  |> snd;

let takeWhile = (predicate, list) =>
  List.fold_left(
    (acc, item) =>
      if (fst(acc) && predicate(item)) {
        (true, List.append(snd(acc), [item]))
      } else {
        (false, snd(acc))
      },
    (true, []),
    list
  )
  |> snd;

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
/*
 let partition = (n, list) =>
   if (n > List.length(list)) {
     []
   } else {
     List.fold_left(
       (acc, item) =>
         if (acc |> fst |> List.length == n - 1) {
           ([], List.append(snd(acc), [List.append(fst(acc), [item])]))
         } else {
           (List.append(fst(acc), [item]), snd(acc))
         },
       ([], []),
       list
     )
     |> snd
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
   if (List.length(remainder) > 0) {
     List.append(partitions, [remainder])
   } else {
     partitions
   }
 };

 let partitionBy = (fn, list) =>
   if (List.length(list) == 0) {
     []
   } else {
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
         (fn(list[0]), [list[0]], []),
         rest(list)
       );
     List.append(value, [r])
   };

 let second = (list) =>
   if (List.length(list) < 2) {
     None
   } else {
     Some(list[1])
   };

 let nth = (index, defaultValue, list) =>
   if (index >= 0 && index < List.length(list)) {
     list[index]
   } else {
     defaultValue
   };

 let last = (list) =>
   if (List.length(list) == 0) {
     None
   } else {
     Some(list[List.length(list) - 1])
   };

 let notEmpty = (list) =>
   if (List.length(list) == 0) {
     None
   } else {
     Some(list)
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

 let empty = (list) => List.length(list) == 0;

 let repeatedly = (n, fn) => List.init(n, (_) => fn());

 let repeat = (n, value) => List.init(n, (_) => value);

 let rec range = (start, _end) =>
   if (start >= _end) {
     []
   } else {
     List.append([start], range(start + 1, _end))
   };

 let dedupe = (list) =>
   if (List.length(list) == 0) {
     []
   } else {
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
         (list[0], list[0], []),
         list
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
   | Some(arr) => List.append(arr, [item])
   };

 let contains = (list, index) => index >= 0 && index < List.length(list);
 */
