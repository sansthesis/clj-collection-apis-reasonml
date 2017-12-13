open Jest;

open Expect;

let even = (a) => a mod 2 == 0;

let () =
  describe(
    "Clj.Array",
    () => {
      describe(
        "first",
        () => {
          test(
            "should retrieve the first element of a non-empty array",
            () => {
              expect([|1, 2|] |> Clj.Array.first) |> toEqual(Some(1));
              expect([|"a"|] |> Clj.Array.first) |> toEqual(Some("a"))
            }
          );
          test(
            "should return None for an empty array",
            () => expect([||] |> Clj.Array.first) |> toEqual(None)
          )
        }
      );
      describe(
        "rest",
        () => {
          test(
            "should return an array of all elements after the first",
            () => {
              expect([|1, 2|] |> Clj.Array.rest) |> toEqual([|2|]);
              expect([|"a", "b", "c"|] |> Clj.Array.rest)
              |> toEqual([|"b", "c"|])
            }
          );
          test(
            "should return an empty array for an array with one element",
            () => {
              expect([|1|] |> Clj.Array.rest) |> toEqual([||]);
              expect([|"a"|] |> Clj.Array.rest) |> toEqual([||])
            }
          );
          test(
            "should return an empty array for an empty array",
            () => expect([||] |> Clj.Array.rest) |> toEqual([||])
          )
        }
      );
      describe(
        "next",
        () => {
          test(
            "should return an array of all elements after the first",
            () => {
              expect([|1, 2|] |> Clj.Array.next) |> toEqual(Some([|2|]));
              expect([|"a", "b", "c"|] |> Clj.Array.next)
              |> toEqual(Some([|"b", "c"|]))
            }
          );
          test(
            "should return None for an array with one element",
            () => {
              expect([|1|] |> Clj.Array.next) |> toEqual(None);
              expect([|"a"|] |> Clj.Array.next) |> toEqual(None)
            }
          );
          test(
            "should return None for an empty array",
            () => expect([||] |> Clj.Array.next) |> toEqual(None)
          )
        }
      );
      describe(
        "cons",
        () =>
          test(
            "should return a new array with an item at the front",
            () => {
              expect([||] |> Clj.Array.cons(1)) |> toEqual([|1|]);
              expect([|"b"|] |> Clj.Array.cons("a")) |> toEqual([|"a", "b"|])
            }
          )
      );
      describe(
        "filter",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj.Array.filter(even)) |> toEqual([||])
          );
          test(
            "should return an empty array when no elements match",
            () => expect([|1|] |> Clj.Array.filter(even)) |> toEqual([||])
          );
          test(
            "should return an array with only elements that match",
            () => {
              expect([|2, 1, 3, 4|] |> Clj.Array.filter(even))
              |> toEqual([|2, 4|]);
              expect(
                [|"a", "b", "a", "c"|]
                |> Clj.Array.filter((letter) => letter == "a")
              )
              |> toEqual([|"a", "a"|])
            }
          )
        }
      );
      /*describe(
          "distinct",
          () => {
            test(
              "should return an empty array when given an empty array",
              () => expect([||] |> Clj.Array.distinct) |> toEqual([||])
            );
            test(
              "should return an array with no duplicate elements",
              () =>
                expect([|1, 2, 1, 1, 2, 3|] |> Clj.Array.distinct)
                |> toEqual([|1, 2, 3|])
            )
          }
        )*/
      describe(
        "remove",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj.Array.remove(even)) |> toEqual([||])
          );
          test(
            "should return an empty array when no elements match",
            () => expect([|2|] |> Clj.Array.remove(even)) |> toEqual([||])
          );
          test(
            "should return an array with only elements that don't match",
            () =>
              expect([|2, 1, 3, 4|] |> Clj.Array.remove(even))
              |> toEqual([|1, 3|])
          )
        }
      );
      describe(
        "keep",
        () => {
          let contrived = (number) =>
            if (number mod 2 == 0) {
              Some(number + 10)
            } else {
              None
            };
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj.Array.keep(contrived)) |> toEqual([||])
          );
          test(
            "should remove all values that the fn returns None for",
            () =>
              expect([|1, 3, 5|] |> Clj.Array.keep(contrived)) |> toEqual([||])
          );
          test(
            "should retain values that the fn returns Some(value) for",
            () =>
              expect([|2, 1, 4, 6, 3, 5, 8|] |> Clj.Array.keep(contrived))
              |> toEqual([|12, 14, 16, 18|])
          )
        }
      );
      describe(
        "interpose",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj.Array.interpose(1)) |> toEqual([||])
          );
          test(
            "should insert the delimiter between elements",
            () =>
              expect([|0, 2|] |> Clj.Array.interpose(1))
              |> toEqual([|0, 1, 2|])
          )
        }
      );
      describe(
        "drop",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj.Array.drop(1)) |> toEqual([||])
          );
          test(
            "should return an empty array when dropping more than it has",
            () => expect([|1|] |> Clj.Array.drop(10)) |> toEqual([||])
          );
          test(
            "should remove the first N elements",
            () =>
              expect([|1, 2, 3, 4|] |> Clj.Array.drop(2)) |> toEqual([|3, 4|])
          )
        }
      );
      describe(
        "dropWhile",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj.Array.dropWhile(even)) |> toEqual([||])
          );
          test(
            "should return the source array when the first result is false",
            () =>
              expect([|1, 2|] |> Clj.Array.dropWhile(even))
              |> toEqual([|1, 2|])
          );
          test(
            "should return the suffix of array starting at the index of the first false result",
            () =>
              expect([|4, 2, 1, 2, 3|] |> Clj.Array.dropWhile(even))
              |> toEqual([|1, 2, 3|])
          )
        }
      )
    }
  );
