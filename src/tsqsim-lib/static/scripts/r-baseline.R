# This function is invoked by the PredictorRBaseline class

predict <- function(a) {
  cat("R received: ", a, "\n");
  b <- c(0, a) # Add 0 at front
  return(head(b, -1)) # Remove last element
  #return(a + 1)
}
