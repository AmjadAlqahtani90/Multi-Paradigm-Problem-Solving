(* Functional statistics using immutable lists and higher-order functions. *)

let mean numbers =
  let total = List.fold_left ( + ) 0 numbers in
  float_of_int total /. float_of_int (List.length numbers)

let median numbers =
  let sorted = List.sort compare numbers in
  let n = List.length sorted in
  if n mod 2 = 1 then
    float_of_int (List.nth sorted (n / 2))
  else
    let lower = List.nth sorted (n / 2 - 1) in
    let upper = List.nth sorted (n / 2) in
    (float_of_int lower +. float_of_int upper) /. 2.0

let mode numbers =
  let frequencies =
    List.fold_left
      (fun counts value ->
        let previous =
          try List.assoc value counts with Not_found -> 0
        in
        (value, previous + 1) :: List.remove_assoc value counts)
      [] numbers
  in
  let highest =
    List.fold_left (fun maximum (_, count) -> max maximum count)
      0 frequencies
  in
  if highest <= 1 then []
  else
    frequencies
    |> List.filter (fun (_, count) -> count = highest)
    |> List.map fst
    |> List.sort compare

let () =
  print_endline "Enter integers separated by spaces:";
  try
    let numbers =
      read_line ()
      |> String.split_on_char ' '
      |> List.filter (fun item -> String.trim item <> "")
      |> List.map int_of_string
    in
    if numbers = [] then
      print_endline "Please enter at least one integer."
    else begin
      Printf.printf "Mean: %.2f\n" (mean numbers);
      Printf.printf "Median: %.2f\n" (median numbers);
      match mode numbers with
      | [] -> print_endline "Mode: No mode (all values occur once)"
      | modes ->
          Printf.printf "Mode: %s\n"
            (String.concat ", " (List.map string_of_int modes))
    end
  with
  | Failure _ -> print_endline "Invalid input: integers only."
