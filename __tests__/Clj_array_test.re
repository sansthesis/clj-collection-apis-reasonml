open Jest;

open Expect;

let even = (a) => a mod 2 == 0;

let () =
  describe(
    "Clj_array",
    () => {
      describe(
        "first",
        () => {
          test(
            "should retrieve the first element of a non-empty array",
            () => {
              expect([|1, 2|] |> Clj_array.first) |> toEqual(Some(1)) |> ignore;
              expect([|"a"|] |> Clj_array.first) |> toEqual(Some("a"))
            }
          );
          test(
            "should return None for an empty array",
            () => expect([||] |> Clj_array.first) |> toEqual(None)
          )
        }
      );
      describe(
        "rest",
        () => {
          test(
            "should return an array of all elements after the first",
            () => {
              expect([|1, 2|] |> Clj_array.rest) |> toEqual([|2|]) |> ignore;
              expect([|"a", "b", "c"|] |> Clj_array.rest)
              |> toEqual([|"b", "c"|])
            }
          );
          test(
            "should return an empty array for an array with one element",
            () => {
              expect([|1|] |> Clj_array.rest) |> toEqual([||]) |> ignore;
              expect([|"a"|] |> Clj_array.rest) |> toEqual([||])
            }
          );
          test(
            "should return an empty array for an empty array",
            () => expect([||] |> Clj_array.rest) |> toEqual([||])
          )
        }
      );
      describe(
        "next",
        () => {
          test(
            "should return an array of all elements after the first",
            () => {
              expect([|1, 2|] |> Clj_array.next)
              |> toEqual(Some([|2|]))
              |> ignore;
              expect([|"a", "b", "c"|] |> Clj_array.next)
              |> toEqual(Some([|"b", "c"|]))
            }
          );
          test(
            "should return None for an array with one element",
            () => {
              expect([|1|] |> Clj_array.next) |> toEqual(None) |> ignore;
              expect([|"a"|] |> Clj_array.next) |> toEqual(None)
            }
          );
          test(
            "should return None for an empty array",
            () => expect([||] |> Clj_array.next) |> toEqual(None)
          )
        }
      );
      describe(
        "cons",
        () =>
          test(
            "should return a new array with an item at the front",
            () => {
              expect([||] |> Clj_array.cons(1)) |> toEqual([|1|]) |> ignore;
              expect([|"b"|] |> Clj_array.cons("a")) |> toEqual([|"a", "b"|])
            }
          )
      );
      describe(
        "filter",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.filter(even)) |> toEqual([||])
          );
          test(
            "should return an empty array when no elements match",
            () => expect([|1|] |> Clj_array.filter(even)) |> toEqual([||])
          );
          test(
            "should return an array with only elements that match",
            () => {
              expect([|2, 1, 3, 4|] |> Clj_array.filter(even))
              |> toEqual([|2, 4|])
              |> ignore;
              expect(
                [|"a", "b", "a", "c"|]
                |> Clj_array.filter((letter) => letter == "a")
              )
              |> toEqual([|"a", "a"|])
            }
          )
        }
      );
      describe(
        "distinct",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.distinct) |> toEqual([||])
          );
          test(
            "should return an array with no duplicate elements",
            () =>
              expect([|1, 2, 1, 1, 2, 3|] |> Clj_array.distinct)
              |> toEqual([|1, 2, 3|])
          )
        }
      );
      describe(
        "remove",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.remove(even)) |> toEqual([||])
          );
          test(
            "should return an empty array when no elements match",
            () => expect([|2|] |> Clj_array.remove(even)) |> toEqual([||])
          );
          test(
            "should return an array with only elements that don't match",
            () =>
              expect([|2, 1, 3, 4|] |> Clj_array.remove(even))
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
            () => expect([||] |> Clj_array.keep(contrived)) |> toEqual([||])
          );
          test(
            "should remove all values that the fn returns None for",
            () =>
              expect([|1, 3, 5|] |> Clj_array.keep(contrived)) |> toEqual([||])
          );
          test(
            "should retain values that the fn returns Some(value) for",
            () =>
              expect([|2, 1, 4, 6, 3, 5, 8|] |> Clj_array.keep(contrived))
              |> toEqual([|12, 14, 16, 18|])
          )
        }
      );
      describe(
        "interpose",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.interpose(1)) |> toEqual([||])
          );
          test(
            "should insert the delimiter between elements",
            () =>
              expect([|0, 2|] |> Clj_array.interpose(1))
              |> toEqual([|0, 1, 2|])
          )
        }
      );
      describe(
        "drop",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.drop(1)) |> toEqual([||])
          );
          test(
            "should return an empty array when dropping more than it has",
            () => expect([|1|] |> Clj_array.drop(10)) |> toEqual([||])
          );
          test(
            "should remove the first N elements",
            () =>
              expect([|1, 2, 3, 4|] |> Clj_array.drop(2)) |> toEqual([|3, 4|])
          )
        }
      );
      describe(
        "dropWhile",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.dropWhile(even)) |> toEqual([||])
          );
          test(
            "should return the source array when the first result is false",
            () =>
              expect([|1, 2|] |> Clj_array.dropWhile(even))
              |> toEqual([|1, 2|])
          );
          test(
            "should return the suffix of array starting at the index of the first false result",
            () =>
              expect([|4, 2, 1, 2, 3|] |> Clj_array.dropWhile(even))
              |> toEqual([|1, 2, 3|])
          )
        }
      );
      describe(
        "take",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.take(10)) |> toEqual([||])
          );
          test(
            "should return the source array when taking more than it has",
            () => expect([|1|] |> Clj_array.take(10)) |> toEqual([|1|])
          );
          test(
            "should return the first N elements from the array",
            () =>
              expect([|1, 2, 3, 4|] |> Clj_array.take(2)) |> toEqual([|1, 2|])
          )
        }
      );
      describe(
        "takeNth",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.takeNth(2)) |> toEqual([||])
          );
          test(
            "should return the source array when N is 1",
            () =>
              expect([|1, 2, 3|] |> Clj_array.takeNth(1))
              |> toEqual([|1, 2, 3|])
          );
          test(
            "should return every Nth item in the array",
            () => {
              expect([|1, 2, 3, 4, 5, 6, 7|] |> Clj_array.takeNth(3))
              |> toEqual([|1, 4, 7|])
              |> ignore;
              expect([|1, 2, 3, 4, 5, 6|] |> Clj_array.takeNth(3))
              |> toEqual([|1, 4|])
            }
          )
        }
      );
      describe(
        "takeWhile",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.takeWhile(even)) |> toEqual([||])
          );
          test(
            "should return an empty array when the first element is false",
            () =>
              expect([|1, 2, 3|] |> Clj_array.takeWhile(even)) |> toEqual([||])
          );
          test(
            "should return the prefix of the array until the predicate is false",
            () =>
              expect([|2, 4, 6, 1, 2, 3, 4|] |> Clj_array.takeWhile(even))
              |> toEqual([|2, 4, 6|])
          )
        }
      );
      describe(
        "butLast",
        () => {
          test(
            "should return None when given an empty array",
            () => expect([||] |> Clj_array.butLast) |> toEqual(None)
          );
          test(
            "should return None when given an array with one element",
            () => expect([|1|] |> Clj_array.butLast) |> toEqual(None)
          );
          test(
            "should return an array of every element but the last in it",
            () =>
              expect([|1, 2, 3|] |> Clj_array.butLast)
              |> toEqual(Some([|1, 2|]))
          )
        }
      );
      describe(
        "dropLast",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.dropLast(5)) |> toEqual([||])
          );
          test(
            "should return an empty array when dropping more than the array has",
            () => expect([|1, 2|] |> Clj_array.dropLast(5)) |> toEqual([||])
          );
          test(
            "should return the source array when dropping 0",
            () =>
              expect([|1, 2|] |> Clj_array.dropLast(0)) |> toEqual([|1, 2|])
          );
          test(
            "should return an array of everything but the last N elements",
            () =>
              expect([|1, 2, 3, 4, 5|] |> Clj_array.dropLast(2))
              |> toEqual([|1, 2, 3|])
          )
        }
      )
    }
  );