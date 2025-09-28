## Solution Overview

- **Thread Safety**: Each philosopher has its own mutex to protect shared data access
- **Fork Assignment**: Philosophers are assigned consecutive forks in a circular arrangement
- **Fork Acquisition**: **Resource Hierarchy** - philosophers always take the lower-numbered fork first to prevent deadlocks
- **Death Monitoring**: A separate monitor thread checks for philosopher deaths
- **Timing Logic**: Last meal time is updated after eating completes (not when it starts)

## Key Features

- Prevents race conditions through per-philosopher mutexes
- Handles both even and odd numbers of philosophers
- Uses resource hierarchy to prevent deadlocks
- Proper cleanup of all resources

## Timing Considerations

**Even Numbers of Philosophers**: Work reliably with tight timing constraints (e.g., 800ms time_to_die, 200ms eat/sleep).

**Odd Numbers of Philosophers**: Now work reliably with the resource hierarchy approach! The program successfully runs indefinitely with:
- 5 philosophers, 1000ms time_to_die, 200ms eat/sleep ✅
- More generous timing also works: 5 philosophers, 1200ms+ time_to_die ✅

**Tight Timing (800ms)**: May still cause starvation deaths with odd numbers due to fork waiting times exceeding time_to_die. This is expected behavior for the Dining Philosophers problem with very tight constraints.

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

### Examples

```bash
# Even number - works with tight timing
./philo 4 800 200 200

# Odd number - works with generous timing
./philo 5 1000 200 200

# Odd number - may fail with very tight timing (expected)
./philo 5 800 200 200
```