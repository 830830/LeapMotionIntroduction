#include "Leap.h"
#include "LeapTouch.h"

class SampleListener : public Leap::Listener
{
public:

    // ����������
    virtual void onInit(const Leap::Controller& controller )
    {
        // �A�v���P�[�V�������o�b�N�O���E���h�ł�Leap����̃t���[���f�[�^���󂯎���悤�ɂ���
        controller.setPolicyFlags( Leap::Controller::PolicyFlag::POLICY_BACKGROUND_FRAMES );

        // �X�N���[���̕��ƍ������擾����
        auto screen = controller.locatedScreens()[0];
        windowWidth = screen.widthPixels();
        windowHeight = screen.heightPixels();

        // �~�W�F�X�`���[�̔F����L���ɂ���
        controller.enableGesture( Leap::Gesture::Type::TYPE_CIRCLE );

        // �^�b�`���͂̏��������s��
        TouchInput::Initialize();
    }

    // �t���[���X�V����
    virtual void onFrame(const Leap::Controller& controller )
    {
        // �V�����t���[�����擾����
        auto frame = controller.frame();

        // �|�C���^���擾����
        Leap::PointableList pointables = frame.pointables();
        if ( pointables.empty() ) {
            return;
        }

        // �ŏ��̃|�C���^�̈ʒu���^�b�`�̈ʒu�Ƃ���
        auto& pointable = pointables[0];
        Leap::Vector normalizedPosition = frame.interactionBox()
                                            .normalizePoint( pointable.stabilizedTipPosition() );
        int x = (int)min( normalizedPosition.x * windowWidth, windowWidth - 1 );
        int y = (int)min( windowHeight - normalizedPosition.y * windowHeight, windowHeight - 1 );

        // �z�o�[
        if ( pointable.touchDistance() > 0 &&
             pointable.touchZone() != Leap::Pointable::Zone::ZONE_NONE) {
            touch.hover( x, y );
        }
        // �^�b�`
        else if( pointable.touchDistance() <= 0 ) {
            touch.touch( x, y );
        }
        // �^�b�`���ĂȂ�
        else {
            touch.up();
        }

        // �~�̃W�F�X�`���[�� Windows �L�[�������A�X�^�[�g���j���[�ɖ߂�
        for ( auto g : frame.gestures() ) {
            if ( (g.type() == Leap::Gesture::Type::TYPE_CIRCLE) &&
                 (g.state() == Leap::Gesture::State::STATE_STOP) ) {
                keybd_event( VK_LWIN, 0, 0, 0 );
                keybd_event( VK_LWIN, 0, KEYEVENTF_KEYUP, 0 );
                break;
            }
        }
    }

private:

    LeapTouch touch;

    int windowWidth;
    int windowHeight;
};

// main()
void main()
{
    Leap::Controller leap;
    SampleListener listener;
    leap.addListener( listener );

    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();

    leap.removeListener( listener );
}

