from load_data import SimData, load_data


def print_data(data: SimData):
    print(data.states)
    print(data.states.shape)
    print(data.states[0])


def main():
    data = load_data()
    print_data(data)


if __name__ == "__main__":
    main()
