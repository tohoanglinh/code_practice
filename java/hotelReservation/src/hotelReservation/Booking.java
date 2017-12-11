/**
 * 
 */
package hotelReservation;

import java.util.ArrayList;
import java.util.Scanner;

class Room
{
    private String roomID = null;
    private boolean booked = false;
    
    Room(String roomID)
    {
        this.roomID = roomID;
    }
    
    String getRoomID()
    {
        return roomID;
    }
    
    void cancel()
    {
        booked = false;
    }
    
    boolean isBooked()
    {
        return booked;
    }
    
    public void setBooked(boolean booked)
    {
        this.booked = booked;
    }
}

class RoomDB
{
    private ArrayList<Room> room;
    private String[] roomID = {"Room1", "Room2", "Room3"};
    
    RoomDB()
    {
        room = new ArrayList<Room>();
        for (int i = 0; i < roomID.length; i++)
        {
            addRoom(new Room(roomID[i]));
        }
    }
    
    public void addRoom(Room addRoom)
    {
        room.add(addRoom);
    }
    
    public ArrayList<Room> getRoom()
    {
        return room;
    }
}


/**
 * @author LinhTH8
 *
 */
public class Booking {

    /**
     * @param args
     */
    
    static RoomDB roomDB = new RoomDB();
    
    public static void main(String[] args) {
        String roomID;
        Room room;
        Scanner inputID = new Scanner(System.in);
        
        /* Introduction */
        System.out.println("--------------------------\n");
        System.out.println("HOTEL ROOM BOOKING Module:\n");
        System.out.println("--------------------------\n");
        while (true)
        {
            while (true)
            {
                System.out.println("Current rooms status:\n");
                System.out.println(getRoomList(roomDB));
                System.out.println("--------------------------\n");
                System.out.println("Please choose a room?\n");
                roomID = inputID.nextLine();
                
                if (roomID.equals("q"))
                {
                    System.out.println("Quit");
                    break;
                }
                
                if (getRoom(roomID) == null)
                {
                    System.out.println("The room ID is incorrect, please enter again\n");
                }
                else
                {
                    room = getRoom(roomID);
                    
                    if (!room.isBooked())
                    {
                        System.out.println("[THANKS] " + roomID + " has been booked successfully\n");
                        room.setBooked(true);
                        break;
                    }
                    else
                    {
                        System.out.println("[BUSY] " + roomID + " was booked by other, please make another choice\n");
                    }
                }
            }
        }
    }

    public static String getRoomList(RoomDB roomDB)
    {
        String roomList = "";
        
        for(Room r:roomDB.getRoom())
        {
            if (!r.isBooked())
            {
                roomList = roomList + r.getRoomID() + " is free \n";
            }
            else
            {
                roomList = roomList + r.getRoomID() + " has been booked \n";
            }
        }
        return roomList;
    }
    
    public static Room getRoom(String roomID)
    {
        for(Room r:roomDB.getRoom())
        {
            if (r.getRoomID().equals(roomID))
            {
                return r;
            }
        }
        return null;
    }
}
