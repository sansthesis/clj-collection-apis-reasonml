open Jest;

open Expect;

let even = (a) => a mod 2 == 0;

let identity = (a) => a;

let () =
  describe(
    "Clj_option",
    () =>
      describe(
        "filter",
        () => {
          test(
            "should return None when given None",
            () => expect(None |> Clj_option.filter(even)) |> toEqual(None)
          );
          test(
            "should return None when predicate(o) is false",
            () => expect(Some(1) |> Clj_option.filter(even)) |> toEqual(None)
          );
          test(
            "should return Some(o) when predicate(o) is true and o is not None",
            () =>
              expect(Some(2) |> Clj_option.filter(even)) |> toEqual(Some(2))
          )
        }
      )
  );
