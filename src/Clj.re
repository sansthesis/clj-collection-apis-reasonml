module Array = {
  let first = (array) =>
    switch (Array.length(array)) {
    | 0 => None
    | _ => Some(array[0])
    };
};
