//=============================================================================
// Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#ifndef PGR_FC2_BUSMANAGER_H
#define PGR_FC2_BUSMANAGER_H

#include "FlyCapture2Platform.h"
#include "FlyCapture2Defs.h"

namespace FlyCapture2
{
    class Error;
    class TopologyNode;

    /**
     * Bus event callback function prototype. Defines the syntax of the
     * callback function that is passed into RegisterCallback() and
     * UnregisterCallback(). It is recommended that minimal handling be
     * performed in this callback as it will block internal processing
     * of bus events until it returns.
     */
    typedef void (*BusEventCallback)( void* pParameter, unsigned int serialNumber );

    /**
     * Handle that is returned when registering a callback. It is required
     * when unregistering the callback.
     */
    typedef void* CallbackHandle;

    /**
     * The BusManager class provides the functionality for the user to get an
     * PGRGuid for a desired camera or device easily. Once the
     * camera or device token is found, it can then be used to connect to the
     * camera or device through the camera class or device class. In addition,
     * the BusManager class provides the ability to be notified when a camera
     * or device is added or removed or some event occurs on the PC.
     */
    class FLYCAPTURE2_API BusManager
    {
        public:

            /**
             * Default constructor.
             */
            BusManager();

            /**
             * Default destructor.
             */
            virtual ~BusManager();

            /**
             * Fire a bus reset. The actual bus reset is only fired for the
             * specified 1394 bus, but it will effectively cause a global bus
             * reset for the library.
             *
             * @param pGuid PGRGuid of the camera or the device to cause bus reset.
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error FireBusReset( PGRGuid* pGuid);

            /**
             * Gets the number of cameras attached to the PC.
             *
             * @param pNumCameras The number of cameras attached.
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetNumOfCameras( unsigned int* pNumCameras );

            /**
             * Gets the PGRGuid for a camera with the specified IPv4 address.
             *
             * @param ipAddress IP address to get GUID for.
             * @param pGuid Unique PGRGuid for the camera.
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetCameraFromIPAddress(
                    IPAddress ipAddress,
                    PGRGuid* pGuid );

            /**
             * Gets the PGRGuid for a camera on the PC. It uniquely identifies
             * the camera specified by the index and is used to identify the camera
             * during a Camera::Connect() call.
             *
             * @param index Zero based index of camera.
             * @param pGuid Unique PGRGuid for the camera.
             *
             * @see GetCameraFromSerialNumber()
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetCameraFromIndex(
                    unsigned int index,
                    PGRGuid*     pGuid );

            /**
             * Gets the PGRGuid for a camera on the PC. It uniquely identifies
             * the camera specified by the serial number and is used to identify the camera
             * during a Camera::Connect() call.
             *
             * @param serialNumber Serial number of camera.
             * @param pGuid Unique PGRGuid for the camera.
             *
             * @see GetCameraFromIndex()
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetCameraFromSerialNumber(
                    unsigned int serialNumber,
                    PGRGuid*     pGuid );

            /**
             * Gets the serial number of the camera with the specified index.
             *
             * @param index Zero based index of desired camera.
             * @param pSerialNumber Serial number of camera.
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetCameraSerialNumberFromIndex(
                    unsigned int  index,
                    unsigned int* pSerialNumber );

            /**
             * Gets the interface type associated with a PGRGuid. This is useful
             * in situations where there is a need to enumerate all cameras
             * for a particular interface.
             *
             * @param pGuid The PGRGuid to get the interface for.
             * @param pInterfaceType The interface type of the PGRGuid.
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetInterfaceTypeFromGuid(
                    PGRGuid *pGuid,
                    InterfaceType* pInterfaceType );

            /**
             * Gets the number of devices. This may include hubs, host controllers
             * and other hardware devices (including cameras).
             *
             * @param pNumDevices The number of devices found.
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetNumOfDevices( unsigned int* pNumDevices );

            /**
             * Gets the PGRGuid for a device. It uniquely identifies the device
             * specified by the index.
             *
             * @param index Zero based index of device.
             * @param pGuid Unique PGRGuid for the device.
             *
             * @see GetNumOfDevices()
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetDeviceFromIndex(
                    unsigned int index,
                    PGRGuid*     pGuid );

            /**
             * Read a phy register on the specified device. The full address
             * to be read from is determined by the page, port and address.
             *
             * @param guid PGRGuid of the device to read from.
             * @param page Page to read from.
             * @param port Port to read from.
             * @param address Address to read from.
             * @param pValue Value read from the phy register.
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error ReadPhyRegister(
                    PGRGuid guid,
                    unsigned int page,
                    unsigned int port,
                    unsigned int address,
                    unsigned int* pValue );

            /**
             * Write a phy register on the specified device. The full address
             * to be written to is determined by the page, port and address.
             *
             * @param guid PGRGuid of the device to write to.
             * @param page Page to write to.
             * @param port Port to write to.
             * @param address Address to write to.
             * @param value Value to write to phy register.
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error WritePhyRegister(
                    PGRGuid guid,
                    unsigned int page,
                    unsigned int port,
                    unsigned int address,
                    unsigned int value );

            /**
             * Read usb link info for the port that the specified device is connected to.
             *
             * @param guid PGRGuid of the device to read from.
             * @param pValue Value read from the card register.
             * <pre>
             * Bit 15:0  = Link %Error Count. Default = 0. This field returns the number of link errors detected by the port.
             * Bit 19:16 = Rx Lane Count. Default = 0. This field that identifies the number of Receive Lanes negotiated by the port.
             * Bit 23:20 = Tx Lane Count. Default = 0. This field that identifies the number of Transmit Lanes negotiated by the port.
             * Bit 31:24 = Reserved.
             *
             * Refer to XHCI 1.1 section 5.4.10 for Port Link Info:<br>
             * <a href="https://www.intel.com/content/dam/www/public/us/en/documents/technical-specifications/extensible-host-controler-interface-usb-xhci.pdf">eXtensible Host Controller interface for USB xHCI</a>
             * </pre>
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetUsbLinkInfo(
                    PGRGuid guid,
                    unsigned int* pValue );

            /**
             * Read usb port status for the port that the specified device is connected to.
             *
             * @param guid PGRGuid of the device to read from.
             * @param pValue Value read from the card register.
             * <pre>
             * Bit 0 = Current Connect Status. Default = 0.
             *         1 = A device is connected to the port
             *         0 = A device is not connected.
             *         This value reflects the current state of the port, and may not correspond directly to the event that caused the Connect Status Change (CSC) bit to be set to 1.
             * Bit 1 = Port Enabled/Disabled. Default = 0. 1 = Enabled. 0 = Disabled.
             * Bit 2 = Reserved.
             * Bit 3 = Over-current Active. Default = 0.
             *         1 = This port currently has an over-current condition.
             *         0 = This port does not have an over-current condition.
             * Bit 4 = Port Reset. Default = 0.
             *         1 = Port Reset signaling is asserted.
             *         0 = Port is not in Reset.
             * Bit 8:5 = Port Link State. Default = RxDetect(5). This field is used to power manage the port and reflects its current link state.
             * Bit 9 = Port Power. Default = 1. This flag reflects a port's logical, power control state.
             *         0 = This port is in the powered-off state.
             *         1 = This port is not in the powered-off state.
             * Bit 13:10 = Port Speed. Default = 0. This field identifies the speed of the connected USB Device. This field is only relevant if a device is connected, in all other cases this field shall indicate Undefined Speed.
             *             0 : Undefined speed
             *             1-15 : Protocol Speed ID (refer to other sections)
             * Bit 15:14 = Port Indicator Control. Default = 0. 0 = Port indicators are off.
             *             1 = Amber. 2 = Green. 3 = Undefined.
             * Bit 16 = Port Link State Write Strobe. Default = 0.
             *          When this bit is set to 1 on a write reference to this register, this flag enables writes to the PLS field.
             * Bit 17 = Connect Status Change. Default = 0.
             *          1 = Change in current connect status. 0 = No change.
             * Bit 18 = Port Enabled/Disabled Change. Default = 0.
             *          1 = change in PED. 0 = No change.
             * Bit 19 = Warm Port Reset Change. Default = 0. This bit is set when Warm Reset processing on this port completes.
             *          0 = No change. 1 = Warm Reset complete.
             * Bit 20 = Over current change. Default = 0.
             *          This bit shall be set to a 1 when there is a 0 to 1 or 1 to 0 transition of Over-current Active.
             * Bit 21 = Port Reset Change. Default = 0. This flag is set to 1 due to a 1 to 0 transition of Port Reset.
             * Bit 22 = Port Link State Change. Default = 0. This flag is set to 1 due to PLS transitions (refer to document)
             * Bit 23 = Port Config %Error Change. Default = 0. This flag indicates that the port failed to configure its link partner.
             *          0 = No change. 1 = Port Config %Error detected.
             * Bit 24 = Cold Attach Status. Default = 0.
             *          1 = Far-end receiver terminations were detected in the disconnected state and the root hub port state machine was unable to advance to the enabled state.
             *          0 - This flag is 0 if PP is 0 or for USB2 protocol parts.
             * Bit 25 = Wake on Connect Enable. Default = 0. Writing this bit to a 1 enables to port to be sensitive to device connects as system wake up events.
             * Bit 26 = Wake on Disconnect Enable. Default = 0. Writing this bit to a 1 enables the port to be sensitive to device disconnects as system wake up events.
             * Bit 27 = Wake on Over-current Enable. Default = 0. Writing this bit to a 1 enables the port to be sensitive to over-current conditions as system wake up events.
             * Bit 29:28 = Reserved
             * Bit 30 = Device Removable. This flag indicates if this port has a removable device attached.
             *          1 = Device is non-removable. 0 = Device is removable.
             * Bit 31 = Warm Port Reset. Default = 0. This flag shall always return 0 when read. Refer to document for writing.
             *
             * Refer to XHCI 1.1 section 5.4.8 for Port Status:<br>
             * <a href="https://www.intel.com/content/dam/www/public/us/en/documents/technical-specifications/extensible-host-controler-interface-usb-xhci.pdf">eXtensible Host Controller interface for USB xHCI</a>
             * </pre>
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetUsbPortStatus(
                    PGRGuid guid,
                    unsigned int* pValue );

            /**
             * Gets the topology information for the PC.
             *
             * @param pNode TopologyNode object that will contain the topology
             *              information.
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error GetTopology(
                    TopologyNode* pNode );

            /**
             * Register a callback function that will be called when the
             * specified callback event occurs.
             *
             * @param busEventCallback Pointer to function that will receive
             the callback.
             * @param callbackType Type of callback to register for.
             * @param pParameter Callback parameter to be passed to callback.
             * @param pCallbackHandle Unique callback handle used for
             *                        unregistering callback.
             *
             * @see UnregisterCallback()
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error RegisterCallback(
                    BusEventCallback    busEventCallback,
                    BusCallbackType     callbackType,
                    void*               pParameter,
                    CallbackHandle*     pCallbackHandle );

            /**
             * Unregister a callback function.
             *
             * @param callbackHandle Unique callback handle.
             *
             * @see RegisterCallback()
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error UnregisterCallback( CallbackHandle callbackHandle );

            /**
             * Force a rescan of the buses. This does not trigger a bus reset.
             * The camera objects will be invalidated only if the camera network
             * topology is changed (ie. a camera is disconnected or added)
             *
             * @return An Error indicating the success or failure of the function.
             */
            virtual Error RescanBus();

            /**
             * Force the camera with the specific MAC address to the specified
             * IP address, subnet mask and default gateway. This is useful in
             * situations where GigE Vision cameras are using IP addresses
             * in a subnet different from the host's subnet.
             *
             * @param macAddress MAC address of the camera.
             * @param ipAddress IP address to set on the camera.
             * @param subnetMask Subnet mask to set on the camera.
             * @param defaultGateway Default gateway to set on the camera.
             *
             * @return An Error indicating the success or failure of the function.
             */
            static Error ForceIPAddressToCamera(
                    MACAddress macAddress,
                    IPAddress ipAddress,
                    IPAddress subnetMask,
                    IPAddress defaultGateway );

            /**
             * Force all cameras on the network to be assigned sequential IP addresses
             * on the same subnet as the netowrk adapters that they are connected to.
             * This is useful in situations where GigE Vision cameras are using
             * IP addresses in a subnet different from the host's subnet.
             *
             * @return An Error indicating the success or failure of the function.
             */
            static Error ForceAllIPAddressesAutomatically();

            /**
             * Force a camera on the network to be assigned an IP address
             * on the same subnet as the netowrk adapters that it is connected to.
             * This is useful in situations where GigE Vision cameras are using IP
             * addresses in a subnet different from the host's subnet.
             *
             * @return An Error indicating the success or failure of the function.
             */
            static Error ForceAllIPAddressesAutomatically(unsigned int serialNumber);

            /**
             * Discover all cameras connected to the network even if they reside
             * on a different subnet. This is useful in situations where GigE Vision
             * cameras are using IP addresses in a subnet different from the host's
             * subnet. After discovering the camera, it is easy to use
             * ForceIPAddressToCamera() to set a different IP configuration.
             *
             * @param gigECameras Pointer to an array of CameraInfo structures.
             * @param arraySize Size of the array. Number of discovered cameras
             *                  is returned in the same value.
             *
             * @return An Error indicating the success or failure of the function.
             *         If the error is PGRERROR_BUFFER_TOO_SMALL then arraySize will
             *         contain the minimum size needed for gigECameras array.
             */
            static Error DiscoverGigECameras(
                    CameraInfo* gigECameras,
                    unsigned int* arraySize  );

            /**
             * Query CCP status on camera with corresponding PGRGuid. This is
             * useful to determine if a GigE camera can be controlled.
             *
             * @param pGuid PGRGuid of the camera
             * @param pControlable Indicates whether camera is controllable
             *
             * @return An Error indicating the success or failure of the function.
             */
            Error IsCameraControlable(
                    PGRGuid* pGuid, bool* pControlable );

        private:

            BusManager( const BusManager& );
            BusManager& operator=( const BusManager& );

            struct BusManagerData; // Forward declaration

            BusManagerData* m_pBusManagerData;
    };
}

#endif //PGR_FC2_BUSMANAGER_H
