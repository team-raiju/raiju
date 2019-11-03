#if !defined(__FSM_H__)
#define __FSM_H__

typedef enum fsm_state {
    INIT,
    IDLE,
    RC,
    AUTO,
    STRATEGY,
} fsm_state_t;

typedef enum strategy {
    ONE, TWO, THREE, FOUR,
} strategy_t;

typedef struct fsm {
    fsm_state_t current_state;

    strategy_t  selected_strategy;
} fsm_t;

void fsm_init(fsm_t* fsm);

void fsm_cycle(fsm_t* fsm);

#endif // __FSM_H__
