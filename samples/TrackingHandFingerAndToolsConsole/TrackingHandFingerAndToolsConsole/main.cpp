#include <Leap.h>

class SampleListener : public Leap::Listener
{
    int handId;

public :

    SampleListener()
    {
        handId = -1;
    }

    void onFrame( const Leap::Controller& leap )
    {
        auto frame = leap.frame();

#if 0
        // ����̃t���[���Ō��o�������ׂĂ̎�A�w�A�c�[��
        Leap::HandList hands = frame.hands();
        Leap::FingerList fingers = frame.fingers();
        Leap::ToolList tools = frame.tools();
        Leap::PointableList pointables = frame.pointables();

        std::cout << "Frame Data : " 
            << " Hands    : " << hands.count()
            << " Fingers  : " << fingers.count() 
            << " Tools    : " << tools.count() 
            << " Pointers : " << pointables.count()
            << std::endl;
#endif

#if 0
        // ���ID����A�������ǐՂ�������
        if ( handId == -1 ) {
            handId = frame.hands()[0].id();
        }
        else {
            Leap::Hand hand = frame.hand( handId );
            handId = hand.id();

            // ��̏���\������
            std::cout << "ID : " << hand.id()
                << " �ʒu : " << hand.palmPosition()
                << " ���x : " << hand.palmVelocity()
                << " �@�� : " << hand.palmNormal()
                << " ���� : " << hand.direction()
                << std::endl;
        }
#endif

#if 0
        // ��ԍ��A�E�A��O�̎���擾����
        Leap::HandList hands = frame.hands();
        Leap::Hand leftMost = hands.leftmost();
        Leap::Hand rightMost = hands.leftmost();
        Leap::Hand frontMost = hands.frontmost();

        std::cout << " �� : " << leftMost.palmPosition() 
                  << " �E : " << rightMost.palmPosition()
                  << " ��O : " << frontMost.palmPosition()
                  << std::endl;
#endif

#if 0
        // ��ɑ����Ă���w�ƃc�[�����擾����
        for ( auto hand : frame.hands() ) {
            std::cout << "ID : " << hand.id()
                << " Pointers : " << hand.pointables().count()
                << " Fingers  : " << hand.fingers().count() 
                << " Tools    : " << hand.tools().count() 
                << std::endl;
        }
#endif

#if 0
        Leap::Finger finger = frame.fingers()[0];
        std::cout << "ID : " << finger.id()
            << " �ʒu : " << finger.tipPosition()
            << " ���x : " << finger.tipVelocity()
            << " ���� : " << finger.direction()
            << std::endl;
#endif
    }
};

void main()
{
    SampleListener listener;
    Leap::Controller leap( listener );

    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();
}
