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
};
