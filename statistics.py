class StatisticsCalculator:
    """Calculate mean, median, and mode for a non-empty list of integers."""

    def __init__(self, numbers):
        if not numbers:
            raise ValueError("The list cannot be empty.")
        if any(type(number) is not int for number in numbers):
            raise ValueError("All values must be integers.")
        self.numbers = list(numbers)

    def calculate_mean(self):
        return sum(self.numbers) / len(self.numbers)

    def calculate_median(self):
        ordered = sorted(self.numbers)
        middle = len(ordered) // 2
        if len(ordered) % 2:
            return float(ordered[middle])
        return (ordered[middle - 1] + ordered[middle]) / 2.0

    def calculate_mode(self):
        frequencies = {}
        for number in self.numbers:
            frequencies[number] = frequencies.get(number, 0) + 1

        highest = max(frequencies.values())
        if highest == 1:
            return []
        return sorted(
            number for number, count in frequencies.items()
            if count == highest
        )


def main():
    try:
        numbers = [int(item) for item in input(
            "Please enter integers separated by spaces: "
        ).split()]
        calculator = StatisticsCalculator(numbers)
        print(f"Mean: {calculator.calculate_mean():.2f}")
        print(f"Median: {calculator.calculate_median():.2f}")
        modes = calculator.calculate_mode()
        if modes:
            print("Mode:", ", ".join(map(str, modes)))
        else:
            print("Mode: No mode (all values occur once)")
    except ValueError as error:
        print(f"Invalid input: {error}")


if __name__ == "__main__":
    main()
