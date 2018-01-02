let filter = (predicate, o) =>
  switch o {
  | None => None
  | Some(x) =>
    if (predicate(x)) {
      Some(x)
    } else {
      None
    }
  };

let isEmpty = (o) =>
  switch o {
  | None => true
  | Some(_) => false
  };

let map = (fn, o) =>
  switch o {
  | None => None
  | Some(x) => Some(fn(x))
  };

let nonEmpty = (o) =>
  switch o {
  | None => false
  | Some(_) => true
  };

let getOrElse = (default, o) =>
  switch o {
  | None => default
  | Some(x) => x
  };
