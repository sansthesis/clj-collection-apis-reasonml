let even = (n) => n mod 2 == 0;

let odd = (n) => n mod 2 == 1;

let any = (_) => true;

let neg = (n) => n < 0;

let nil = (a) =>
  switch a {
  | None => true
  | Some(_) => false
  };

let pos = (n) => n >= 0;

let some = (a) =>
  switch a {
  | None => false
  | Some(_) => true
  };

let zero = (n) => n == 0;
