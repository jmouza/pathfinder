#include "settings.h"

#include <memory>

class UIElementsManager
{
private:
    std::shared_ptr<Settings> settings = nullptr;

    bool CreateButton(const char* label, const char* tool_tip, bool enabled = true) const;
    void CreateSlider(const char* label, int *val, int min, int max, const char* format, const char* tool_tip) const;
    void CreateSelector() const;
    bool ButtonShouldBeEnabled(const char* button_string);

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
    void HandleAlgorithmSelector(enum Algorithm selected_algorithm) const;

    void ShowHelpWindow() const;

    void ChangeState(State target_state);
public:
    UIElementsManager(std::shared_ptr<Settings> _settings): settings(_settings) {}
    void CreateUIElements();
    void WriteStateText() const;
};