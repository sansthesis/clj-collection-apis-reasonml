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
