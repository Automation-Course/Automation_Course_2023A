# class holds all logic required for the calculation
class Calculator:

    DECIMAL_TO_BINARY = '10->2'
    BINARY_TO_DECIMAL = '2->10'

    def __init__(self):
        self.mode = self.DECIMAL_TO_BINARY
        self.quit = False
    
    # Checks the input and call the relevant function.
    def handle_input(self, user_input):
        if user_input == 'quit':
            print('quitting..')
            self.quit = True
        elif user_input == 'mode':
            print("current mode: " + self.mode)
        elif calculator.is_change_mode_input(user_input):
            calculator.switch_mode(user_input)
            print("switched mode: " + self.mode)
        else:
            result = calculator.calculate(user_input)
            print(result)

    # Calculates output by current mode. ensure input is valid first.
    def calculate(self, user_input):
        self.ensure_input_is_valid(user_input)
        if self.mode == self.DECIMAL_TO_BINARY:
            result = self.decimal_to_binary(user_input)
        else:
            result = self.binary_to_decimal(user_input)
        return result

    # Change calculation mode by user's input.
    def switch_mode(self, mode):
        if mode == self.DECIMAL_TO_BINARY:
            self.mode = self.DECIMAL_TO_BINARY
        else:
            self.mode = self.BINARY_TO_DECIMAL

    def should_quit(self):
        return self.quit

    # Checks if the input is a change mode command
    def is_change_mode_input(self, user_input):
        return user_input == self.DECIMAL_TO_BINARY or user_input == self.BINARY_TO_DECIMAL

    def ensure_input_is_valid(self, user_input):
        self.ensure_input_is_all_digits(user_input)
        if self.mode == self.BINARY_TO_DECIMAL:
            self.ensure_input_is_binary(user_input)
        elif self.mode == self.DECIMAL_TO_BINARY:
            self.ensure_input_is_decimal(user_input)

    def ensure_input_is_all_digits(self, user_input):
        if not user_input.isdigit():
            raise Exception()

    def ensure_input_is_binary(self, user_input):
        for char in user_input:
            if char != '0' and char != '1':
                raise Exception()

    def ensure_input_is_decimal(self, user_input):
        if len(user_input) > 1 and user_input.startswith('0'):
            raise Exception()
        try:
            int(user_input)
        except ValueError:
            raise Exception()

    def decimal_to_binary(self, user_input):
        user_input = int(user_input)
        if user_input == 0:
            return '0'
        result = ''
        while user_input > 0:
            result = str(user_input % 2) + result
            user_input = user_input // 2

        return result

    def binary_to_decimal(self, user_input):
        result = 0
        power = len(user_input) - 1
        for char in user_input:
            if char == '1':
                result += 2**power
            power = power - 1
        return result


print("-----------------------------")
print("Decimal <-> Binary Calculator")
print("-----------------------------")
calculator = Calculator()  # Create calculator instance
while not calculator.should_quit():  # Run until user quits.
    user_input = input()  # Receive input from user

    # Try to handle input. In case of error - print to user.
    try:
        calculator.handle_input(user_input)
    except Exception:
        print("Bad input")
