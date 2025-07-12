#include "ui_elements_observers.h"
#include "gui/state_manager.h"

#include <memory>
#include <vector>

class UIElementsManager
{
private:
    std::vector<std::shared_ptr<IStartButtonObserver>> StartButtonObservers;
    std::vector<std::shared_ptr<IPauseButtonObserver>> PauseButtonObservers;
    std::vector<std::shared_ptr<IResetButtonObserver>> ResetButtonObservers;
    std::vector<std::shared_ptr<IClearButtonObserver>> ClearButtonObservers;
    std::vector<std::shared_ptr<INextButtonObserver>> NextButtonObservers;
    std::vector<std::shared_ptr<IPreviousButtonObserver>> PreviousButtonObservers;
    std::vector<std::shared_ptr<IForwardButtonObserver>> ForwardButtonObservers;
    std::vector<std::shared_ptr<IBackwardButtonObserver>> BackwardButtonObservers;
    std::vector<std::shared_ptr<IFinerGridButtonObserver>> FinerGridButtonObservers;
    std::vector<std::shared_ptr<ICoarserGridButtonObserver>> CoarserGridButtonObservers;

    bool CreateButtonAndButtonPressed(const char* label, const char* tool_tip, bool enabled = true) const;
    void CreateSlider(const char* label, int *val, int min, int max, const char* format, const char* tool_tip) const;
    void CreateSelector() const;
    bool ButtonShouldBeEnabledInState(const char* button_string, State current_state) const;

    void HandleStartButton();
    void HandlePauseButton();
    void HandleResetButton();
    void HandleClearButton();
    void HandleNextButton();
    void HandlePreviousButton();
    void HandleForwardButton();
    void HandleBackwardButton();
    void HandleFinerGridButton();
    void HandleCoarserGridButton();
    void HandleHelpButton() const;
    // void HandleAlgorithmSelector(enum Algorithm selected_algorithm) const;

    void ShowHelpWindow() const;
public:
    void CreateUIElements(State current_state, bool start_and_finish_cell_set, bool increment_possible, bool decrement_possible, bool cell_size_increasable, bool cell_size_decreasable, int* current_speed);
    void WriteStateText(State current_state, int current_step, int max_steps) const;
    void AttachStartButtonObserver(std::shared_ptr<IStartButtonObserver> observer) {StartButtonObservers.push_back(observer);}
    void AttachPauseButtonObserver(std::shared_ptr<IPauseButtonObserver> observer) {PauseButtonObservers.push_back(observer);}
    void AttachResetButtonObserver(std::shared_ptr<IResetButtonObserver> observer) {ResetButtonObservers.push_back(observer);}
    void AttachClearButtonObserver(std::shared_ptr<IClearButtonObserver> observer) {ClearButtonObservers.push_back(observer);}
    void AttachNextButtonObserver(std::shared_ptr<INextButtonObserver> observer) {NextButtonObservers.push_back(observer);}
    void AttachPreviousButtonObserver(std::shared_ptr<IPreviousButtonObserver> observer) {PreviousButtonObservers.push_back(observer);}
    void AttachForwardButtonObserver(std::shared_ptr<IForwardButtonObserver> observer) {ForwardButtonObservers.push_back(observer);}
    void AttachBackwardButtonObserver(std::shared_ptr<IBackwardButtonObserver> observer) {BackwardButtonObservers.push_back(observer);}
    void AttachFinerGridButtonObserver(std::shared_ptr<IFinerGridButtonObserver> observer) {FinerGridButtonObservers.push_back(observer);}
    void AttachCoarserGridButtonObserver(std::shared_ptr<ICoarserGridButtonObserver> observer) {CoarserGridButtonObservers.push_back(observer);}
};