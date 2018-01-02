let filter = (predicate, o: option('a)) =>
  switch o {
  | None => None
  | Some(x) =>
    if (predicate(x)) {
      Some(x)
    } else {
      None
    }
  };
