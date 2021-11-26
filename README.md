# tsqsim
Time Series Quick Simulator - able to perform time series analysis and to setup validation experiments.

## Background
[Time Series Analysis](https://en.wikipedia.org/wiki/Time_series) deals with finding patterns in Time Series data, 
which can be just anything that changes across time and depends on values from the previous discrete time points. 
The patterns can be used to build a model of the data, that can be in turn used to predict future data points 
up to a certain confidence, which decreases gradually, as the requested prediction horizon expands.

## The dangers of modeling
As with just every model for every single task, it's much easier to optimize a model to work great for the data known at the moment of optimization (_in-sample_), 
rather than to make it generic and work even just satisfactory enough on new, yet unknown data (_out-of-sample_). 
The problem is known as [overfitting](https://en.wikipedia.org/wiki/Overfitting) and is, or at least should be, 
the most important concern of every data scientist. 
In order to mitigate the problem and help you create generic models, the project employs [Walk Forward Optimization (or Validation)](https://en.wikipedia.org/wiki/Walk_forward_optimization), 
which simulates the lack of future data at the exact discrete moment of trying to find the optimal parameters, as well as [Monte Carlo simulation](https://en.wikipedia.org/wiki/Monte_Carlo_methods_in_finance) 
of alternative scenarios, generated randomly, yet still based on the original data. 
The combination of these two methods serves as the ultimate stress-test method. 
Remember, that the _observed history_ is just the single story line out of many possibilities, that could have happened. 
What we observe is simply something that just happened to agree to collapse into one story line, 
based on the probabilities attached to the set of interacting events in question, including those with low probability but impact so high, 
that it can break the (almost) agreed story line.
If something dramatic could have happened, but was avoided only because of sheer luck, it will happen in future in an altered constellation, given enough time. 
You'd best be ready by fortifying your model (through simulation) against these dramatic events and their alterations. 
Please refer to [_"Fooled by Randomness"_](https://en.wikipedia.org/wiki/Fooled_by_Randomness) by Nassim Nicholas Taleb for more details.

# Quickstart
In case these instructions become outdated, please refer to the steps of the [CI](.github/workflows/build.yml).

## Requirements
Supported systems:
- Ubuntu 20.04 / Debian-stable
- ~~Mac OSX~~ (soon)
- ~~Windows~~ (somewhat later)

## Preparation
Please run the below scripts. They are meant to be non-interactive and will require root permissions (via `sudo`). 
When in doubt, please view their contents with `cat` for an objective assessment of their functionalities.
```bash
git clone --recursive https://github.com/mj-xmr/tsqsim.git # Clone this repo (assuming it's not a fork)
cd tsqsim		# Enter the cloned repo's dir
./util/deps-pull.sh	# Download the maintaned dependencies
./util/deps-build.sh	# Build and install the unmanaged dependencies (uses sudo for installation)
./util/prep-env.sh	# Prepare the environment - downloads example data and creates useful symlinks
```

## Building & running
```bash
./ci-default --run-demo	# Build and optionally run the demo
./ci-default -h 	# See all build options
```
The executables will be available under `build/*/bin`, where `*` depends on the choices you've just made above.

# Controlling the application
To learn all the app's options and additional information, from within the target build directory (`build/*/bin`) execute:
```bash
./tsqsim --help
```

## Command line example
For example, to override the default discrete period and the ending year, the following can be executed:
```bash
./tsqsim --per h12 --max-year 2016
```

## Modifying the transformation script
The TS transformation script's path can be obtained via `./tsqsim --help`, as well as it's currently available transformations. The script can modify the chain of transformations used by the executable, without the need for its recompilation.

# Acknowledgments
The project uses a lot of code written by me in the previous 10+ years. 
I’m now decoupling it and making it reusable for generic purposes.
The development of this project is currently being financed by the generous Monero Community (MC). 
Thus the priorities of the development are skewed towards delivering results to the MC.


