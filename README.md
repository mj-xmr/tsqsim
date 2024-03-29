# tsqsim
Time Series Quick Simulator - able to perform time series analysis 
and to setup validation experiments.
With its somewhat limited plotting capabilities, 
but highly optimized run time speed, the simulator serves more as a stress-tester 
of your models, challenging their robustness, rather than a pattern discovery tool. 
The assumption is that some preliminary research has already been done, 
using scripting languages like `Python`, `R` or `Weka`, where patterns are easy to eyball. 
Teaching a machine to detect these found patterns automatically in rigorous conditions 
is where the `tsqsim` shows its true potential.

## Background
[Time Series Analysis (TSA)](https://en.wikipedia.org/wiki/Time_series) deals with finding patterns in Time Series data, 
which can be just anything that changes across time and depends on values from the previous discrete time points. 
The patterns can be used to build a model of the data, that can be in turn used to predict future data points 
up to a certain confidence, which decreases gradually, as the requested prediction horizon expands.

In order to understand better what the project does, or the TSA in general, I recommend watching [this playlist](https://www.youtube.com/watch?v=ZoJ2OctrFLA&list=PLvcbYUQ5t0UHOLnBzl46_Q6QKtFgfMGc3).

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
that they can break the (almost) agreed story line.
If something dramatic could have happened, but was avoided only because of sheer luck, it will happen in future in an altered constellation, given enough time. 
You'd best be ready by fortifying your model (through simulation) against these dramatic events and their alterations. 
Please refer to [_"Fooled by Randomness"_](https://en.wikipedia.org/wiki/Fooled_by_Randomness) by Nassim Nicholas Taleb if you are interested in learning such concepts.

# Requirements
- The console simulator should be compilable and run fast enough on almost any OS, where a POSIX C++ compiler is available. 
- About 1.5 GB of RAM is expected for the initial data serialization step.
- Depending on the granuality of your data, the according data storage space is needed for the textual (CSV) input, as well as for the serialized binary data. Both types of data are stored compressed though and are being decompressed on the fly into memory, as they are needed.

Supported Operating Systems and features:

| OS \ Feature  | CI | gcc | clang | UT | wx | Qt | Py | R  |
| ------------- | -- | --- | ----- | -- | -- | -- | -- | -- |
| Debian stable |    | ✓   | ✓     |  ✓ | ✓  | ✓  | ✓  | ✓  |
| Debian buster |    | ✓   | ✓     |  ✓ | ✓  | ✓  | ✓  | ✓  |
| Ubuntu 21.04  |    | ✓   | ✓     |  ✓ | ✓  | ✓  | ✓  | ✓  |
| Ubuntu 20.04  | ✓  | ✓   | ✓     |  ✓ | ✓  | ✓  | ✓  | ✓  |
| Mac OSX 11    | ✓  |     | ✓     |  ✓ | ✓  | ✓  | ✓  | ✓  |
| Mac OSX 10.15 | ✓  |     | ✓     |  ✓ | ✓  |    | ✓  |    |
| Windows       | ✓  | ✓   |       |  ✓ |    |    | ✓  |    |

Glossary:
- CI = [Continuous Integration](https://github.com/mj-xmr/tsqsim/actions)
- gcc & clang = C/C++ compilers
- UT = [Unit Tests](https://en.wikipedia.org/wiki/Unit_testing)
- wx = [wxWidgets](https://www.wxwidgets.org/)-based configuration application
- Qt = [Qt](https://en.wikipedia.org/wiki/Qt_(software)) application (data viewer)
- Py = [Python](https://en.wikipedia.org/wiki/Python_(programming_language)) alternative to the QT app
- R = bindings to the ["R" statistical framework](https://www.r-project.org/)

Optional components:
- UT
- wx
- Qt
- Py
- R

# Quickstart
In case these instructions become outdated, please refer to the steps of the [CI](.github/workflows/build.yml).

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
./ci-default --no-qt # Don't build the optional QT module
./ci-default -h 	# See all build options
```
The executables will be available under `build/*/bin`, where `*` depends on the choices you've just made above.

## Rebuilding new versions
```bash
cd tsqsim             # Enter the cloned repo's dir
git fetch             # Get new tags
git checkout master   # Checkout master or a specific tag
git pull
git submodule update --remote; git submodule sync && git submodule update # Update the submodules
rm build/* -fr        # Sometimes it might be needed to clean the build dir, if the directory structure changes
./util/prep-env.sh
./util/deps-pull.sh
./util/deps-build.sh
```

# Controlling the application
To learn all the app's options and additional information, from within the target build directory (`build/*/bin`) execute:
```bash
./tsqsim --help
```
Some of the options are able to be modified more conviniently through the `wxConf` application, accessible from the same directory (TODO: add more help):
```bash
./wxConf
```
The changes made in `wxConf` are being read by all of the remaining applications right after performing any change in the `wxConf`, without any need of confirmation of the changes.

## Command line example
For example, to override the default discrete period and the ending year, the following can be executed:
```bash
./tsqsim --per h12 --max-year 2016  # Simulator
./tsqsim-qt --min-year 2015 --max-year 2016 --per h12   # QT data viewer
```
Any alterations performed via the CLI override the changes made in the `wxConf` app. In case of the QT app though, the CLI options overwrite the configurations permanently, which is a system limitation. They can be however regenerated at any time by the `wxConf`.

## Controlling the WX configurator
Beside the usual application usage, please note, that it's very beneficial to use mouse scroll on the selection controls, like Months or Years, which eases their operation.

## Controlling the QT data viewer
- Mouse right click reloads the data. Useful after a configuration has changed via `wxConf`
- Mouse scroll zooms in and out
- Mouse drag with left click moves the viewpoint within the same dataset
- Cursors left/right move the viewpoint left/right, loading new dataset
- Cursors up/down scale up/down
- Control resets the state of the app completely and returns to the initial view

## Modifying the transformation script
The TS transformation script's path can be obtained via `./tsqsim --help`, as well as it's currently available transformations. The script can modify the chain of transformations used by the executable, without the need for its recompilation.

## Running R scripts
The tool delivers binding to the R's C interface, currently via `PredictorRBaseline` and `PredictorRCustom`. Their corresponding R scripts can be found in the directory `static/scripts`
Before running the wrapped R scripts, two variables need to be exported from the shell, that is supposed to run the predictors. Under Linux:
```
export R_HOME=/usr/lib/R
export LD_LIBRARY_PATH=$R_HOME/lib
./tsqsim
```

and under OSX:

```
export R_HOME=/Library/Frameworks/R.framework/Resources
export LD_LIBRARY_PATH=$R_HOME/lib
./tsqsim
```

## Python backends
`tsqsim` is able to wrap the Python 3rd party TSA frameworks. You may either write your own wrapper or use the already available ones.

### Available python backends
The following Python backends are currently available:

| Name  | installation | script |
| ----- | ------------ | ------ |
| [statsmodels](https://www.statsmodels.org/) | pip install darts | scripts/py_darts.py |
| [darts](https://github.com/unit8co/darts) |  pip install statsmodels  | scripts/py_statsmodels.py |

### Extending python backends
TODO! Wrap predict and convert from dataframe and return a timeseries.

# Development
For the development use case, it's recommended to turn on certain optimizations, that reduce the recompilation and linking time while changing the source code often. The optimizations are: dynamic linking (*shared*), precompiled headers (*pch*) and (optionally) a networked parallel compiler's wrapper, [icecc](https://github.com/icecc/icecream).

A command, that would leverage these optimizations could look like the following:
```bash
./ci-default --shared --pch --compiler icecc -j 30
```
, where `icecc` is available only after [setting it up](docs/ICECC_INSTALL.md) in your LAN, and `30` would be the number of cores, that you want to use through icecc. If you declare more, than there are available, the icecc scheduler will throttle down your choice automatically.
To spare yourself typing, I recommend adding the following aliases to your shell:
```bash
echo "alias tsqdev='./ci-default --shared --pch --compiler icecc -j 30'" >> ~/.bash_aliases
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

# Example outputs
## QT data viewer

![image](https://user-images.githubusercontent.com/63722585/144647510-51028542-a4a7-497c-9bc1-053daf7af947.png)

## Python-based QT app's alternative
- Upper window: The interactive QT data viewer
- Lower window: A very portable Python alternative, useful where QT is unavailable

![image](https://user-images.githubusercontent.com/63722585/151012558-2751868a-de4d-4a97-bac6-fc599b336d7a.png)

## Python-based (Partial) AutoCorrelation Function (ACF & PACF) plots

ACF of the original series:

![image](https://user-images.githubusercontent.com/63722585/151013189-43f1f028-32ff-4f8c-a8e1-ff9f69bd409d.png)

ACF of the first difference of the series, exhibiting a statistically significant inverse correlation at lag 1:

![image](https://user-images.githubusercontent.com/63722585/151015304-b90e07c0-a2ec-448a-8a18-61ada8687b79.png)

... and so does the Partial AutoCorrelation Function (PACF):

![image](https://user-images.githubusercontent.com/63722585/151221354-f233f937-cbe0-443c-840c-2be77376f24e.png)

Seasonal decomposition of the daily bars exhibits a strong seasonal pattern over the week:

![image](https://user-images.githubusercontent.com/63722585/151616487-d26419cd-89db-462a-946a-0eedc4a4e7c9.png)



## wx Configurator
![image](https://user-images.githubusercontent.com/63722585/151012395-0b984207-cfa3-468d-81ca-d2da10132091.png)


## Console simulator

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


