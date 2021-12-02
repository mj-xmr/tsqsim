# tsqsim
Time Series Quick Simulator - able to perform time series analysis 
and to setup validation experiments.
With its somewhat limited plotting capabilities, 
but highly optimized run time speed, the simulator serves more as a stress-tester 
of your models, challenging their robustness. 
The assumption is that some preliminary research has already been done, 
using scripting languages like `Python`, `R` or `Weka`, where patterns are easy to eyball. 
Teaching a machine to detect these patterns automatically in rigorous conditions 
is where the `tsqsim` shows its true potential.

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
./util/prep-env.sh	# Prepare the environment - downloads example data and creates useful symlinks
./util/deps-pull.sh	# Download the maintaned dependencies
./util/deps-build.sh	# Build and install the unmanaged dependencies (uses sudo for installation)
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

# Development
For the development use case, it's recommended to turn on certain optimizations, that reduce the recompilation and linking time while changing the source code often. The optimizations are: dynamic linking, unity build and (optionally) a networked parallel compiler's wrapper, [icecc](https://github.com/icecc/icecream).

A command, that would leverage these optimizations could look like the following:
```bash
./ci-default --shared --unity --compiler icecc -j 30
```
, where `icecc` is available only after [setting it up](docs/ICECC_INSTALL.md) in your LAN, and `30` would be the number of cores, that you want to use through icecc. If you declare more, than there are available, the icecc scheduler will throttle down your choice automatically.
To spare yourself typing, I recommend adding the following aliases to your shell:
```bash
echo "alias tsqdev='./ci-default --shared --unity --compiler icecc -j 30'" >> ~/.bash_aliases
echo "alias tsqdev-dbg='tsqdev --debug'" >> ~/.bash_aliases
bash    # To reload the aliases and make them available in the current shell
```

Now you're able to use the aliases from the source directory via:
```bash
tsqdev
```
or, in case you need to debug:
```bash
tsqdev-dbg
```

# Acknowledgments
The project uses a lot of code written by me in the previous 10+ years. 
I’m now decoupling it and making it reusable for generic purposes.
The development of this project is currently being financed by the generous Monero Community (MC). 
Thus the priorities of the development are skewed towards delivering results to the MC.

# Example outputs
```
Reading script file: 'tsqsim-script.txt'
Script line: 'diff'
Script line: 'sqrts # Nice to have before logs'
Script line: 'logs'
Script line: 'add 0'

  Dickey-Fuller GLS Test Results
  ====================================
  Statistic                     -2.049
  P-value                        0.065
  Optimal Lags                       3
  Criterion                        AIC
  Trend                       constant
  ------------------------------------

  Test Hypothesis
  ------------------------------------
  H0: The process contains a unit root
  H1: The process is weakly stationary

  Critical Values
  ---------------
   1%      -2.754
   5%      -2.143
  10%      -1.838

  Test Conclusion
  ---------------
  We can reject H0 at the 10% significance level

Closes & transformation
                                                                             
   1.14 +----------------------------------------------------------------+   
        |       +       +       +        +       +       +       +****** |   
  1.135 |-+                                             * *       *    +-|   
   1.13 |-+      ****                                   ****     *     +-|   
        |      * * **                                  *   **    *       |   
  1.125 |-*   ***    ***                             ***     *   *     +-|   
        | ****       *  *    *      *** *     **     **      ** *        |   
   1.12 |**              *  * * ****   * *   *  *   *          *       +-|   
  1.115 |-+              * **  *         *****   * **                  +-|   
        |       +       + *     +        +       **      +       +       |   
   1.11 +----------------------------------------------------------------+   
        0       10      20      30       40      50      60      70      80  
                                                                             
                                                                             
    2 +------------------------------------------------------------------+   
  1.5 |*+*    +        +    *  +*  **   * ** ** +*     **  *     +   **+-|   
    1 |*+*    *  * *  ***   **  *  * * ** ** * ***   * ** * * *    * * +-|   
      |* *    *  * *  * *   **  *  * * ** ** *   *   * ** * * *    * *   |   
  0.5 |-**    *  * *  * *   **  *  * * ** ** *   *   * ** * * *    * * +-|   
    0 |-**    ** * ** * ** * * * **  * ** * **    *  *** ** * **   **  +-|   
 -0.5 |-* *  *** *****  ** * * * **   * **  **    * * ** *  ** *  * *  +-|   
   -1 |-* *  **** ****  **** * * **   * **  **    * * ** *  ** *  * *  +-|   
      | * ** ** * ** *  * ** * * **   * **  **    *** ** *  ** **** *    |   
 -1.5 |-+ ****+ * ** * +*    **+ *    * **      + * *   +*  **   ** *  +-|   
   -2 +------------------------------------------------------------------+   
      0       10       20      30       40      50      60       70      80  


EURUSD-d - Stats
  Mean            StdDev          URT           Samples
--------------------------------------------------------
-0.150           1.369          -1.251          25
 0.069           1.549          -5.128          25
-0.108           1.443          -4.204          27
--------------------------------------------------------
 0.219           106.6%         -2.049          77

StatsMedianSplit::Stats size = 12.5596
Stationarity score = -2.04925
2019.04 - 2019.06

```


